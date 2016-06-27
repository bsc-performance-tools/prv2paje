#include "prvparser.h"


prv2paje::PrvParser::PrvParser(ifstream *prvStream, prv2paje::PcfParser *pcfParser, prv2paje::InterpreterComponent *interpreterComponent):
    prvStream(prvStream), pcfParser(pcfParser), interpreterComponent(interpreterComponent), prvMetaData(new PrvMetaData())
{

}

prv2paje::PrvParser::~PrvParser()
{
    delete prvMetaData;
}

void prv2paje::PrvParser::parse()
{
    string line;
    long lineNumber=0;
    double *currentTimestamp;
    *currentTimestamp=0;
    Mode mode=Header;
    if (prvStream){
        while(getline(*prvStream,line)){
            lineNumber++;
            if (lineNumber%100000==0){
                Message::Debug(to_string(lineNumber)+ " lines processed");
            }
            replace(line.begin(), line.end(), '\t', ' ');
            std::size_t found = line.find_first_of("(");
            if ((found!=std::string::npos)&&(found+1<line.length())){
                found = line.find_first_of("a", found+1);
            }
            if ((found!=std::string::npos)&&(line[found+1]=='t')&&(found+5<line.length())&&(line[found+5]==':')){
                line[found+5]='*';
            }
            replace(line.begin(), line.end(), PRV_HEADER_QUOTE_IN_CHAR, GENERIC_SEP_CHAR);
            replace(line.begin(), line.end(), PRV_HEADER_QUOTE_OUT_CHAR, GENERIC_SEP_CHAR);
            trim_all(line);
            if (!line.empty()){
                escaped_list_separator<char> sep(GENERIC_ESCAPE_CHAR, PRV_HEADER_SEP_MAIN_CHAR, GENERIC_QUOTE_CHAR);
                tokenizer<escaped_list_separator<char> > tokens(line, sep);
                tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens.begin();
                if (mode==Header){
                    mode=Body;
                    Message::Info("Parsing Header", 2);
                }else{
                    string eventType=*tokensIterator;
                    tokensIterator++;
                    //communicator
                    if (eventType.compare(PRV_BODY_COMMUNICATOR)==0){
                        //do nothing TODO, low priority...
                    //communications
                    }else if (eventType.compare(PRV_BODY_COMMUNICATION)==0){
                        parseCommunications(tokensIterator, currentTimestamp, lineNumber);
                    }else if (eventType.compare(PRV_BODY_EVENTS)==0){
                        parseEvents(tokensIterator, tokens.end(), currentTimestamp, lineNumber);
                    }else if (eventType.compare(PRV_BODY_STATE)==0){
                        parseState(tokensIterator, currentTimestamp, lineNumber);
                    }
                }
            } 
        }
        interpreterComponent->finalize();
    }
}

void prv2paje::PrvParser::parseHeader(tokenizer<escaped_list_separator<char> >::iterator tokensIterator)
{
    Message::Info("Parsing Header", 2);
    string temp=*tokensIterator;
    erase_all(temp, GENERIC_SEP);
    replace(temp.begin(), temp.end(), '*', ':');
    prvMetaData->setComment(temp);
    tokensIterator++;
    Message::Info("Comment: " +temp, 3);
    //duration_unit
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
    Message::Info("Duration: " +to_string(prvMetaData->getDuration())+", Unit: "+prvMetaData->getTimeUnit(), 3);
    Message::Info("Time Divider: " +to_string(prvMetaData->getTimeDivider()), 3);
    //nodes"<cpu>"
    temp=*tokensIterator;
    tokensIterator++;
    //nodes;<cpu>;
    tokensTemp.clear();
    split(tokensTemp, temp, is_any_of(GENERIC_SEP));
    //nodes
    int nodes=atoi(tokensTemp.operator [](PRV_HEADER_SUBFIELD_HW_NODES).c_str());
    prvMetaData->setNodes(nodes);
    Message::Info("Number of nodes: " +to_string(prvMetaData->getNodes()), 3);
    vector<int> * cpus = new vector<int>();
    Message::Info("CPUS:", 3);
    temp=tokensTemp.operator [](PRV_HEADER_SUBFIELD_HW_CPUS);
    split(tokensTemp, temp, is_any_of(PRV_HEADER_SEP_HW_CPUS));
    for (int i=0; i<tokensTemp.size(); i++){
        cpus->push_back(atoi(tokensTemp.operator [](i).c_str()));
        Message::Info("Node: "+to_string(i)+", CPU number: "+to_string(cpus->at(i)), 4);
    }
    prvMetaData->setCpus(cpus);
    //drop what follows, not necessary to rebuild the hierarchy
    //...
    //saving metadata
    Message::Info("Initializing writer", 2);
    Message::Info("Storing metadata", 3);
    interpreterComponent->setPrvMetaData(prvMetaData);
    Message::Info("Storing event types", 3);
    interpreterComponent->setPcfParser(pcfParser);
    interpreterComponent->initialize();
}

void prv2paje::PrvParser::parseEvents(tokenizer<escaped_list_separator<char> >::iterator tokensIterator, tokenizer<escaped_list_separator<char> >::iterator tokensEnd, double * currentTimestamp, long lineNumber)
{
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu=atoi(temp.c_str());
    if (cpu==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return;
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
    double timestamp=stoll(temp)/prvMetaData->getTimeDivider();
    if (*currentTimestamp>timestamp){
        Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(timestamp*prvMetaData->getTimeDivider())+" Previous timestamp: "+to_string(*currentTimestamp*prvMetaData->getTimeDivider())+". Leaving...");
        return;
    }
    *currentTimestamp=timestamp;
    map<int, string>* events=new map<int, string>();
    for (; tokensIterator!=tokensEnd;){
        temp=*tokensIterator;
        tokensIterator++;
        int id=atoi(temp.c_str());
        temp=*tokensIterator;
        tokensIterator++;
        events->operator [](id)=temp;
    }
    interpreterComponent->pushEvents(cpu, app, task, thread, timestamp, events, lineNumber);
    delete events;
}

void prv2paje::PrvParser::parseState(tokenizer<escaped_list_separator<char> >::iterator tokensIterator, double * currentTimestamp, long lineNumber)
{
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu=atoi(temp.c_str());
    if (cpu==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return;
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
    double startTimestamp=stoll(temp)/prvMetaData->getTimeDivider();
    if (*currentTimestamp>startTimestamp){
        Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(startTimestamp*prvMetaData->getTimeDivider())+" Previous timestamp: "+to_string(*currentTimestamp*prvMetaData->getTimeDivider())+". Leaving...");
        return;
    }
    *currentTimestamp=startTimestamp;
    temp=*tokensIterator;
    tokensIterator++;
    double endTimestamp=stoll(temp)/prvMetaData->getTimeDivider();
    temp=*tokensIterator;
    interpreterComponent->pushState(cpu, app, task, thread, startTimestamp, endTimestamp, temp, lineNumber);
}

void prv2paje::PrvParser::parseCommunications(tokenizer<escaped_list_separator<char> >::iterator tokensIterator, double * currentTimestamp, long lineNumber)
{
    string temp=*tokensIterator;
    tokensIterator++;
    int cpu1=atoi(temp.c_str());
    if (cpu1==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return;
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
    double startTimestampSW=stoll(temp)/prvMetaData->getTimeDivider();
    *currentTimestamp=startTimestampSW;
    temp=*tokensIterator;
    tokensIterator++;
    double startTimestampHW=stoll(temp)/prvMetaData->getTimeDivider();
    if (*currentTimestamp>startTimestampHW){
        Message::Critical("line "+ to_string(lineNumber)+". Events are not correctly time-sorted. Current timestamp: "+ to_string(startTimestampHW*prvMetaData->getTimeDivider())+" Previous timestamp: "+to_string(*currentTimestamp*prvMetaData->getTimeDivider())+". Leaving...");
        return;
    }
    temp=*tokensIterator;
    tokensIterator++;
    int cpu2=atoi(temp.c_str());
    if (cpu2==0){
        Message::Warning("line "+ to_string(lineNumber)+". CPU value is 0. Event will be dropped...");
        return;
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
    double endTimestampHW=stoll(temp)/prvMetaData->getTimeDivider();
    temp=*tokensIterator;
    tokensIterator++;
    double endTimestampSW=stoll(temp)/prvMetaData->getTimeDivider();
    temp=*tokensIterator;
    //Communication tag is not retrieved. Should we?
    interpreterComponent->pushCommunications(cpu1, app1, task1, thread1, cpu2, app2, task2, thread2, startTimestampSW, startTimestampHW, endTimestampSW, endTimestampHW, temp, lineNumber);
//events
}
