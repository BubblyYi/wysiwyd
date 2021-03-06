#include <story.h>

using namespace yarp::os;
using namespace yarp::sig;
using namespace wysiwyd::wrdac;
using namespace std;


Bottle story::unfoldGoal(string goal)
{
    bool bVerbose = false;
    Bottle bOutput;

    if (bVerbose) cout << endl << "Starting to unfold: " << goal << endl;

    bool isRole = true;
    bool bIsFirst = true;
    istringstream iss(goal);
    Bottle bTemp;
    do
    {
        string sub;
        iss >> sub;
        if (sub[0] == '(') sub = sub.erase(0, 1);
        if (sub[sub.size() - 1] == ')')   sub = sub.erase(sub.size() - 1);
        if (bVerbose) cout << "Substring: " << sub << endl;
        if (isRole){
            if (!bIsFirst) bOutput.addList() = bTemp;
            bTemp.clear();
            bTemp.addString(sub);
        }
        else{
            bTemp.addString(sub);
        }
        bIsFirst = false;
        isRole = !isRole;

    } while (iss);

    if (bVerbose) cout << "bOutput: " << bOutput.toString() << endl;

    if (bVerbose) cout << "find is: " << bOutput.find("predicate").toString() << endl;

    return bOutput;
}


bool story::displayNarration(bool displayAll)
{
    if (humanNarration.size() > 2){
        cout << endl << "********************************\nbegin narration from human: " << viInstances[0] << " with " << humanNarration.size() << " events and " << sentenceStory.size() << " sentences." << endl;

        if (displayAll){
            for (auto itSt : vEvents){
                itSt.removeUnderscore();
                cout << "\t A:" << itSt.agent;
                cout << "\t P:" << itSt.predicate;
                cout << "\t O:" << itSt.object;
                cout << "\t R:" << itSt.recipient << endl;
            }
        }

        for (auto ii : humanNarration){
            cout << "\t" << ii << endl;
        }

        cout << "********************************" << endl;
        return true;
    }
    else{
        if (sentenceStory.size() > iThresholdSentence){
            cout << endl << "begin display narration of story: " << counter << " with " << vEvents.size() << " events and " << sentenceStory.size() << " sentence." << endl;

            if (displayAll){
                for (auto itSt : vEvents){
                    itSt.removeUnderscore();
                    cout << "\t A:" << itSt.agent;
                    cout << "\t P:" << itSt.predicate;
                    cout << "\t O:" << itSt.object;
                    cout << "\t R:" << itSt.recipient << endl;
                }
            }
            for (auto itSt : sentenceStory){
                cout << itSt;
            }


            cout << "OCW ARE: ";
            for (auto itS = vOCWEvt.begin(); itS != vOCWEvt.end(); itS++){
                cout << *itS << "  ";
            }
            cout << endl << endl;
            return true;
        }
        else{
            yWarning(" Story to short to be displayed");
            return false;
        }
    }
}


void story::addOCW(vector<string> inputOCW){

    for (auto itIn = inputOCW.begin(); itIn != inputOCW.end(); itIn++){
        bool found = false;
        if (*itIn != "none"){

            for (auto itS = vOCWEvt.begin(); itS != vOCWEvt.end(); itS++){
                if (*itS == *itIn){
                    found = true;
                }
            }
            if (!found) vOCWEvt.push_back(*itIn);
        }
    }

}


string story::toString(){
    ostringstream osOut;
    osOut << "counter " << counter << endl << "size of events: " << vEvents.size() << " size of instance: " << viInstances.size() << endl;
    for (auto itSt : vEvents){
        osOut << itSt.agent << "\t" << itSt.predicate << "\t" << itSt.object << "\t" << itSt.recipient << endl;
    }
    string sOutput = osOut.str();
    return sOutput;
}
