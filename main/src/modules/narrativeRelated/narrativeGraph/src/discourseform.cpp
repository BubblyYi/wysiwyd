#include "discourseform.h"
#include <set>
#include <map>

using namespace yarp::os;
using namespace discourseform;
using namespace std;

// get a discourse from speech recog, to lrh, to be put under the good format
string meaningDiscourse::meaningToDiscourseForm(vector<string> vMeaning){
    cout << "Meaning to discourse ... ";
    ostringstream os;
    bool toSkip = false;
    // get each sentence
    for (vector<string>::iterator level1 = vMeaning.begin(); level1 != vMeaning.end(); level1++){
        //level1 is:  OCW, OCW OCW OCW, OCW OCW, P1, P2 A2 O2, P3 A3 ...
        if (*level1 != ""){
            toSkip = false;

            // get the meaning:
            //cout << "level1 is: " << *level1 << endl;
            string delimiter = ",";
            size_t pos = 0;
            string token;
            string s = *level1;
            ostringstream osMeaning;
            int iPAORWordsInProp = 0;
            bool isFirst = true;
            while ((pos = s.find(delimiter)) != string::npos) {
                token = s.substr(0, pos);
                if (!isFirst) { osMeaning << " , "; }
                osMeaning << token;
                iPAORWordsInProp++;
                s.erase(0, pos + delimiter.length());
                //cout << "\t meaning is: " << osMeaning.str() << " - iPAORWordsInProp " << iPAORWordsInProp << endl;
                isFirst = false;
            }
            //cout << s << endl;

            vector<string>  meaningParsed;
            // meaning parsed by spaces and colon
            stringstream stringStream(*level1);
            string line;
            while (getline(stringStream, line))
            {
                size_t prev = 0, pos;
                while ((pos = line.find_first_of(" ,", prev)) != string::npos)
                {
                    if (pos > prev)
                        meaningParsed.push_back(line.substr(prev, pos - prev));
                    prev = pos + 1;
                }
                if (prev < line.length())
                    meaningParsed.push_back(line.substr(prev, string::npos));
            }

            // remove PAOR from meaningParsed:
            vector<string> meaningWords = vector<string>(meaningParsed.begin(), meaningParsed.begin() + meaningParsed.size() / 2);
            vector<string> meaningPAOR = vector<string>(meaningParsed.begin() + meaningParsed.size() / 2, meaningParsed.end());

            //        cout << "    meaningWords:  | ";
            for (vector < string >::iterator itWo = meaningWords.begin();
                itWo != meaningWords.end();
                itWo++){
                //            cout << *itWo << " | ";
            }
            //       cout << endl;

            //       cout << "    meaningPAOR:  | ";
            for (vector < string >::iterator itWo = meaningPAOR.begin();
                itWo != meaningPAOR.end();
                itWo++){
                //         cout << *itWo << " | ";
            }
            //       cout << endl;
            //separation of the propositions

            meaningSentence currentSentence;

            if (meaningPAOR.size() != meaningWords.size()){
                yWarning() << " in narrativeGraph::discourseform.cpp::meaningToDiscourseForm: Size of PAOR and OCW different";
                os << " in narrativeGraph::discourseform.cpp::meaningToDiscourseForm: Size of PAOR and OCW different" << endl;
                for (auto pa : meaningPAOR){
                    cout << pa << " ";
                    os << pa << " ";
                }
                cout << "\t";
                os << "\t";
                for (auto mea : meaningWords){
                    cout << mea << " ";
                    os << mea << " ";
                }
                cout << endl << "PAOR: " << meaningPAOR.size() << "\t OCW: " << meaningWords.size() << endl;
                os << endl << "PAOR: " << meaningPAOR.size() << "\t OCW: " << meaningWords.size() << endl;
                cout << "OCW are : ";
                os << "OCW are: ";
                for (auto oc : meaningWords){
                    cout << oc << "\t";
                    os << oc << "\t";
                }
                cout << endl;
            }
            else{
                for (unsigned int iWords = 0; iWords < meaningPAOR.size(); iWords++){
                    unsigned int iNumberProposition = atoi(&(meaningPAOR[iWords].at(1)));

                    // if new proposition
                    if (currentSentence.vSentence.size() < iNumberProposition){
                        storygraph::PAOR paor;

                        currentSentence.vSentence.push_back(paor);
                    }

                    if (meaningPAOR.size() <= iWords || currentSentence.vSentence.size() <= (iNumberProposition-1) || meaningWords.size() <= iWords){
                        toSkip = true;
                    }

                    if (!toSkip){
                        // add the OCW and PAOR
                        if (meaningPAOR[iWords].at(0) == 'P'){
                            currentSentence.vSentence[iNumberProposition - 1].P = meaningWords[iWords];
                        }
                        if (meaningPAOR[iWords].at(0) == 'A'){
                            currentSentence.vSentence[iNumberProposition - 1].A = meaningWords[iWords];
                        }
                        if (meaningPAOR[iWords].at(0) == 'O'){
                            currentSentence.vSentence[iNumberProposition - 1].O = meaningWords[iWords];
                        }
                        if (meaningPAOR[iWords].at(0) == 'R'){
                            currentSentence.vSentence[iNumberProposition - 1].R = meaningWords[iWords];
                        }
                    }
                }

                if (currentSentence.vSentence.size() != 0 && !toSkip){
                    meanings.vDiscourse.push_back(currentSentence);
                }
            }
        }
    }

    cout << "done." << endl;

    //    print();

    return os.str();
}


void meaningDiscourse::print(){

    cout << "------------------ BEGIN  MEANINGDISCOURSE --------------------" << endl;

    cout << " --------" << endl;;
    for (vector<meaningSentence>::iterator level1 = meanings.vDiscourse.begin();
        level1 != meanings.vDiscourse.end();
        level1++
        )
    {
        for (vector<storygraph::PAOR>::iterator level2 = level1->vSentence.begin();
            level2 != level1->vSentence.end();
            level2++){

            if (level2 == level1->vSentence.begin()){
                cout << "\t ----" << endl;
            }
            // proposition level:
            cout << level2->toString() << "\t";
            //            cout << " \t IGARF linked: " << level2->kmLinkEvt[0].toString() <<endl;

            cout << endl << "\t ----" << endl;
        }
        cout << " --------" << endl;
    }
    cout << "------------------ END  MEANINGDISCOURSE --------------------" << endl;
}
