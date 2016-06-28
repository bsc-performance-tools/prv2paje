#include "prvparser.h"


prvreader::PrvParser::PrvParser(ifstream *prvStream, prvreader::PcfParser *pcfParser):
    prvStream(prvStream), pcfParser(pcfParser), prvMetaData(new PrvMetaData()), mode(Header), lineNumber(0), currentTimestamp(0)
{

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
            if (lineNumber%100000==0){
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
                        prvEvent= new PrvOther();
                    //communications
                    }else if (eventType.compare(PRV_BODY_COMMUNICATION)==0){
                        prvEvent=parseCommunications(tokens, currentTimestamp, lineNumber);
                    }else if (eventType.compare(PRV_BODY_EVENTS)==0){
                        prvEvent=parseEvents(tokens, currentTimestamp, lineNumber);
                    }else if (eventType.compare(PRV_BODY_STATE)==0){
                        prvEvent=parseState(tokens, currentTimestamp, lineNumber);
                    }
                }
                delete tokens;
            } 
        }else{
            prvEvent=new PrvOther(lineNumber);
            prvEvent->setType(prveventtype::End);
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
    PrvEvent* prvEvent=new PrvOther();
    prvEvent->setType(prveventtype::Header);
    return prvEvent;
}

prvreader::PrvEvent* prvreader::PrvParser::parseEvents(tokenizer<escaped_list_separator<char> > *tokens, long currentTimestamp, long lineNumber)
{
    tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
    tokensIterator++;
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu=atoi(temp.c_str());
    if (cpu==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return new PrvOther(lineNumber);
    }
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
    if (currentTimestamp>timestamp){
        Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(timestamp)+" Previous timestamp: "+to_string(currentTimestamp)+". Leaving...");
        return new PrvOther(lineNumber);
    }
    currentTimestamp=timestamp;
    map<int, string>* events=new map<int, string>();
    for (; tokensIterator!=tokens->end();){
        temp=*tokensIterator;
        tokensIterator++;
        int id=atoi(temp.c_str());
        temp=*tokensIterator;
        tokensIterator++;
        events->operator [](id)=temp;
    }
    return new PrvEvents(cpu, app, task, thread, timestamp, lineNumber, events);
}

prvreader::PrvEvent* prvreader::PrvParser::parseState(tokenizer<escaped_list_separator<char> > *tokens, long currentTimestamp, long lineNumber)
{
    tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
    tokensIterator++;
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu=atoi(temp.c_str());
    if (cpu==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return new PrvOther(lineNumber);
    }
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
    if (currentTimestamp>startTimestamp){
        Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(startTimestamp)+" Previous timestamp: "+to_string(currentTimestamp)+". Leaving...");
        return new PrvOther(lineNumber);
    }
    currentTimestamp=startTimestamp;
    temp=*tokensIterator;
    tokensIterator++;
    long endTimestamp=stol(temp);
    temp=*tokensIterator;
    return new PrvState(cpu, app, task, thread, startTimestamp,  lineNumber, endTimestamp, temp);
}

prvreader::PrvEvent* prvreader::PrvParser::parseCommunications(tokenizer<escaped_list_separator<char> > *tokens, long currentTimestamp, long lineNumber)
{
    tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens->begin();
    tokensIterator++;
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu1=atoi(temp.c_str());
    if (cpu1==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return new PrvOther(lineNumber);
    }
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
    currentTimestamp=startTimestampSW;
    temp=*tokensIterator;
    tokensIterator++;
    long startTimestampHW=stol(temp);
    if (currentTimestamp>startTimestampHW){
        Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(startTimestampHW)+" Previous timestamp: "+to_string(currentTimestamp)+". Leaving...");
        return new PrvOther(lineNumber);
    }
    temp=*tokensIterator;
    tokensIterator++;
    int cpu2=atoi(temp.c_str());
    if (cpu2==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return new PrvOther(lineNumber);
    }
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
    //Communication tag is not retrieved. Should we?
    return new PrvCommunications(cpu1, app1, task1, thread1, startTimestampSW, lineNumber, cpu2, app2, task2, thread2, endTimestampSW, startTimestampHW, endTimestampHW, temp);
//events
}

prvreader::PcfParser *prvreader::PrvParser::getPcfParser() const
{
    return pcfParser;
}

prvreader::PrvMetaData *prvreader::PrvParser::getPrvMetaData() const
{
    return prvMetaData;
}
