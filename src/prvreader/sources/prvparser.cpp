/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                                 prvreader                                 *
 *      Libraries and Tools for reading and converting Paraver traces        *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 3        *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/

#include "prvparser.h"


prvreader::PrvParser::PrvParser(ifstream *prvStream, prvreader::PcfParser *pcfParser):
    prvStream(prvStream), pcfParser(pcfParser), prvMetaData(new PrvMetaData()), mode(Header), lineNumber(0), currentTimestamp(0), fast(false)
{
    filter=pcfParser->getFilter();
}

prvreader::PrvParser::PrvParser(ifstream *prvStream, prvreader::PcfParser *pcfParser, bool fast):
    prvStream(prvStream), pcfParser(pcfParser), prvMetaData(new PrvMetaData()), mode(Header), lineNumber(0), currentTimestamp(0), fast(fast)
{
    filter=pcfParser->getFilter();
}

prvreader::PrvParser::~PrvParser()
{
    delete prvMetaData;
}

prvreader::PrvEvent* prvreader::PrvParser::parseLine()
{
    string line;
    PrvEvent* prvEvent;
    if (prvStream){
        if(getline(*prvStream,line)){
            lineNumber++;
            if (lineNumber%10000==0){
                Message::Debug(to_string(lineNumber)+ " lines processed");
            }
            replace(line.begin(), line.end(), '\t', ' ');
            std::size_t found = line.find_first_of("(");
            if ((found!=std::string::npos)&&(found+1<line.length())){
                found = line.find_first_of("a", found+1);
            }
            if ((found!=std::string::npos)&&(line[found+1]=='t')&&(found+5<line.length())&&(line[found+5]==PRV_HEADER_SEP_MAIN_CHAR)){
                line[found+5]='*';
            }
            replace(line.begin(), line.end(), PRV_HEADER_QUOTE_IN_CHAR, GENERIC_SEP_CHAR);
            replace(line.begin(), line.end(), PRV_HEADER_QUOTE_OUT_CHAR, GENERIC_SEP_CHAR);
            trim_all(line);
            if (!line.empty()){
                escaped_list_separator<char> sep(GENERIC_ESCAPE_CHAR, PRV_HEADER_SEP_MAIN_CHAR, GENERIC_QUOTE_CHAR);
                tokenizer<escaped_list_separator<char> > *tokens = new tokenizer<escaped_list_separator<char> >(line, sep);
                tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
                if (mode==Header){
                    prvEvent=parseHeader(tokens);
                    mode=Body;
                }else{
                    string eventType=*tokensIterator;
                    tokensIterator++;
                    //communicator
                    if (eventType.compare(PRV_BODY_COMMUNICATOR)==0){
                        prvEvent= new PrvOther(lineNumber, prveventtype::Skip);
                    //communications
                    }else if (eventType.compare(PRV_BODY_COMMUNICATION)==0){
                        prvEvent=parseCommunications(tokens, lineNumber);
                    }else if (eventType.compare(PRV_BODY_EVENTS)==0){
                        prvEvent=parseEvents(tokens, lineNumber);
                    }else if (eventType.compare(PRV_BODY_STATE)==0){
                        prvEvent=parseState(tokens, lineNumber);
                    }else{
                        prvEvent= new PrvOther(lineNumber, prveventtype::Skip);
                    }
                }
                delete tokens;
            } 
        }else{
            prvEvent=new PrvOther(lineNumber, prveventtype::End);
        }
    }
    return prvEvent;
}

prvreader::PrvEvent* prvreader::PrvParser::parseHeader(tokenizer<escaped_list_separator<char> > *tokens)
{
    tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
    string temp=*tokensIterator;
    erase_all(temp, GENERIC_SEP);
    replace(temp.begin(), temp.end(), '*', ':');
    prvMetaData->setComment(temp);
    tokensIterator++;
    temp=*tokensIterator;
    tokensIterator++;
    vector<string> tokensTemp;
    split(tokensTemp, temp, is_any_of(PRV_HEADER_SEP_DURATION));
    if (tokensTemp.size()>0){
        prvMetaData->setDuration(stol(tokensTemp.operator [](PRV_HEADER_SUBFIELD_DURATION_VALUE)));
    }
    if (tokensTemp.size()>1){
        prvMetaData->setTimeUnit(tokensTemp[PRV_HEADER_SUBFIELD_DURATION_UNIT]);
    }else{
        prvMetaData->setTimeUnit("");
    }
    temp=*tokensIterator;
    tokensIterator++;
    tokensTemp.clear();
    split(tokensTemp, temp, is_any_of(GENERIC_SEP));
    int nodes=atoi(tokensTemp.operator [](PRV_HEADER_SUBFIELD_HW_NODES).c_str());
    prvMetaData->setNodes(nodes);
    vector<int> * cpus = new vector<int>();
    temp=tokensTemp.operator [](PRV_HEADER_SUBFIELD_HW_CPUS);
    split(tokensTemp, temp, is_any_of(PRV_HEADER_SEP_HW_CPUS));
    for (int i=0; i<tokensTemp.size(); i++){
        cpus->push_back(atoi(tokensTemp.operator [](i).c_str()));
    }
    prvMetaData->setCpus(cpus);
    return new PrvOther(lineNumber, prveventtype::Header);
}

prvreader::PrvEvent* prvreader::PrvParser::parseEvents(tokenizer<escaped_list_separator<char> > *tokens, long lineNumber)
{
    if (filter->getDisableEvents()){
        return new PrvOther(lineNumber, prveventtype::Filtered);
    }
    tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
    tokensIterator++;
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int app=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int task=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int thread=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    long timestamp=stol(temp);
    map<int, string>* events=new map<int, string>();
    for (; tokensIterator!=tokens->end();){
        temp=*tokensIterator;
        tokensIterator++;
        int id=atoi(temp.c_str());
        temp=*tokensIterator;
        tokensIterator++;
        if (!filter->isFiltered(id)){
            events->operator [](id)=temp;
        }
    }
    if (!fast){
        if (cpu==0){
            Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
            return new PrvOther(lineNumber, prveventtype::NotConform);
        }
        if (currentTimestamp>timestamp){
            Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(timestamp)+" Previous timestamp: "+to_string(currentTimestamp)+". Leaving...");
            return new PrvOther(lineNumber, prveventtype::Critical);
        }
    }
    currentTimestamp=timestamp;
    return new PrvEvents(cpu, app, task, thread, timestamp, lineNumber, events);
}

prvreader::PrvEvent* prvreader::PrvParser::parseState(tokenizer<escaped_list_separator<char> > *tokens, long lineNumber)
{
    if (filter->getDisableStates()){
        return new PrvOther(lineNumber, prveventtype::Filtered);
    }
    tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
    tokensIterator++;
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu=atoi(temp.c_str());

    temp=*tokensIterator;
    tokensIterator++;
    int app=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int task=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int thread=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    long startTimestamp=stol(temp);
    temp=*tokensIterator;
    tokensIterator++;
    long endTimestamp=stol(temp);
    temp=*tokensIterator;
    if (!fast){
        if (cpu==0){
            Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
            return new PrvOther(lineNumber, prveventtype::NotConform);
        }
        if (currentTimestamp>startTimestamp){
            Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(startTimestamp)+" Previous timestamp: "+to_string(currentTimestamp)+". Leaving...");
            return new PrvOther(lineNumber, prveventtype::Critical);
        }
    }
    currentTimestamp=startTimestamp;
    return new PrvState(cpu, app, task, thread, startTimestamp,  lineNumber, endTimestamp, temp);
}

prvreader::PrvEvent* prvreader::PrvParser::parseCommunications(tokenizer<escaped_list_separator<char> > *tokens, long lineNumber)
{
    if (filter->getDisableCommunications()){
        return new PrvOther(lineNumber, prveventtype::Filtered);
    }
    tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
    tokensIterator++;
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu1=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int app1=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int task1=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int thread1=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    long startTimestampSW=stol(temp);
    temp=*tokensIterator;
    tokensIterator++;
    long startTimestampHW=stol(temp);
    temp=*tokensIterator;
    tokensIterator++;
    int cpu2=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int app2=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int task2=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    int thread2=atoi(temp.c_str());
    temp=*tokensIterator;
    tokensIterator++;
    long endTimestampHW=stol(temp);
    temp=*tokensIterator;
    tokensIterator++;
    long endTimestampSW=stol(temp);
    temp=*tokensIterator;
    if (!fast){
        if (cpu1==0){
            Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
            return new PrvOther(lineNumber, prveventtype::NotConform);
        }
        if (cpu2==0){
            Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
            return new PrvOther(lineNumber, prveventtype::NotConform);
        }
    }
    if (currentTimestamp>startTimestampHW){
        Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(startTimestampHW)+" Previous timestamp: "+to_string(currentTimestamp)+". Leaving...");
        return new PrvOther(lineNumber, prveventtype::Critical);
    }
    /*if (startTimestampHW<startTimestampSW){
        return new PrvOther(lineNumber, prveventtype::NotConform);
    }*/
    currentTimestamp=startTimestampHW;
    //Communication tag is not retrieved. Should we?
    return new PrvCommunications(cpu1, app1, task1, thread1, startTimestampSW, lineNumber, cpu2, app2, task2, thread2, endTimestampSW, startTimestampHW, endTimestampHW, temp);
//events
}

bool prvreader::PrvParser::getFast() const
{
    return fast;
}

void prvreader::PrvParser::setFast(bool value)
{
    fast = value;
}

prvreader::PcfParser *prvreader::PrvParser::getPcfParser() const
{
    return pcfParser;
}

prvreader::PrvMetaData *prvreader::PrvParser::getPrvMetaData() const
{
    return prvMetaData;
}
