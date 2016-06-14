#include "../headers/prvparser.h"


prv2paje::PrvParser::PrvParser(ifstream *prvStream, prv2paje::PcfParser *pcfParser, prv2paje::PajeWriter *pajeWriter):
    prvStream(prvStream), pcfParser(pcfParser), pajeWriter(pajeWriter)
{

}

void prv2paje::PrvParser::parse()
{
    string line;
    int lineNumber=0;
    Mode mode=Header;
    if (prvStream){
        while(getline(*prvStream,line)){
            lineNumber++;
            replace(line.begin(), line.end(), '\t', ' ');
            replace(line.begin(), line.end(), PRV_HEADER_QUOTE_IN_CHAR, GENERIC_QUOTE_CHAR);
            replace(line.begin(), line.end(), PRV_HEADER_QUOTE_OUT_CHAR, GENERIC_QUOTE_CHAR);
            trim_all(line);
            if (!line.empty()){
                escaped_list_separator<char> sep(GENERIC_ESCAPE_CHAR, PRV_HEADER_SEP_MAIN_CHAR, GENERIC_QUOTE_CHAR);
                tokenizer<escaped_list_separator<char> > tokens(line, sep);
                tokenizer<escaped_list_separator<char> >::iterator tokensIterator=tokens.begin();
                if (mode==Header){
                    //comment
                    string temp=*tokensIterator;
                    tokensIterator++;
                    prvMetaData.setComment(temp);
                    //duration_unit
                    temp=*tokensIterator;
                    tokensIterator++;
                    vector<string> tokensTemp;
                    split(tokensTemp, temp, is_any_of(PRV_HEADER_SEP_DURATION));
                    if (tokensTemp.size()>0){
                        prvMetaData.setDuration(stol(tokensTemp.operator [](PRV_HEADER_SUBFIELD_DURATION_VALUE)));
                    }
                    if (tokensTemp.size()>1){
                        prvMetaData.setTimeUnit(tokensTemp[PRV_HEADER_SUBFIELD_DURATION_UNIT]);
                    }else{
                        prvMetaData.setTimeUnit("");
                    }
                    //nodes"<cpu>"
                    temp=*tokensIterator;
                    tokensIterator++;
                    replace(temp.begin(), temp.end(), GENERIC_QUOTE_CHAR, GENERIC_SEP_CHAR);
                    //nodes;<cpu>;
                    tokensTemp.clear();
                    split(tokensTemp, temp, is_any_of(GENERIC_SEP));
                    //nodes
                    int nodes=atoi(tokensTemp.operator [](PRV_HEADER_SUBFIELD_HW_NODES).c_str());
                    prvMetaData.setNodes(nodes);
                    vector<int> * cpus = new vector<int>();
                    temp=*tokensIterator;
                    tokensIterator++;
                    tokensTemp.clear();
                    split(tokensTemp, temp, is_any_of(PRV_HEADER_SEP_HW_CPUS));
                    for (int i=0; i<tokensTemp.size(); i++){
                        cpus->push_back(atoi(tokensTemp.operator [](i).c_str()));
                    }
                    prvMetaData.setCpus(cpus);
                    //drop what follows, not necessary to rebuild the hierarchy
                    //...
                    //saving metadata
                    pajeWriter->setPrvMetaData(prvMetaData);
                    pajeWriter->generatePajeHeader();
                }else{
                    mode=Body;
                    string eventType=*tokensIterator;
                    tokensIterator++;
                    //communicator
                    if (eventType.compare(PRV_BODY_COMMUNICATOR)){
                        //do nothing TODO, low priority...
                    //communications
                    }else if (eventType.compare(PRV_BODY_COMMUNICATION)){
                        //TODO
                    //events
                    }else if (eventType.compare(PRV_BODY_EVENTS)){
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
                        map<int, int>* events=new map<int, int>();
                        for (; tokensIterator!=tokens.end();){
                            temp=*tokensIterator;
                            tokensIterator++;
                            int id=atoi(temp.c_str());
                            temp=*tokensIterator;
                            tokensIterator++;
                            int value=atoi(temp.c_str());
                            events->operator [](id)=value;
                        }
                        pajeWriter->pushEvents(cpu, app, task, thread, timestamp, events);
                        delete events;
                    }else if (eventType.compare(PRV_BODY_STATE)){
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
                        tokensIterator++;
                        int type=atoi(temp.c_str());
                        pajeWriter->pushState(cpu, app, task, thread, startTimestamp, endTimestamp, type);
                    }
                }
            }
        }
    }
}
