#include "petri_net.h"

// Places function

Place::Place(string name = "", int nT = 0) {
    this->name = name;
    this->nTokens = nT;
}

void Place::addToken(int nT) {
    this->nTokens += nT;
}

void Place::minusToken(int nT) {
    if (this->nTokens < nT) return;
    else {
        this->nTokens -= nT;
    }
}

int Place::getToken() {
    return this->nTokens;
}

void Place::setToken(int nT) {
    this->nTokens = nT;
}

void Place::print() {
    cout << "(" << this->name.substr(1, name.length() - 1) << "(" << this->getToken() << "))";
}

//Transititon
void Transition::addArcOut(Place* p) {
    out.push_back(p);
}

void Transition::addArcIn(Place* p) {
    in.push_back(p);
}

bool Transition::isEnabled() {
    for (auto it = in.begin(); it != in.end(); ++it) {
        if ((*it)->getToken() == 0) return false;
    }

    return true;
}

void Transition::firing() {
    if (this->isEnabled()) {
        for (auto it = in.begin(); it != in.end(); ++it) {
            (*it)->minusToken(1);
        }
        for (auto it = out.begin(); it != out.end(); ++it) {
            (*it)->addToken(1);
        }
    }
}

void Transition::print() {
    cout << "[" << this->name.substr(1, name.length() - 1) << "]";
}

// Net function
Place* Net::getPlace(string name) {
    for (auto it = p.begin(); it != p.end(); ++it) {
        if ((*it)->name == name) return *it;
    }
    return nullptr;
}

Transition* Net::getTrans(string name) {
    for (auto it = t.begin(); it != t.end(); ++it) {
        if ((*it)->name == name) return *it;
    }

    return nullptr;
}

void Net::addPlace(string name, int token = 0) {
    p.push_back(new Place(name, token));
}

void Net::addTransition(string name) {
    t.push_back(new Transition(name));
}

void Net::addArcOut(string t, string p) {
    Place* pP = getPlace(p);
    Transition* pT = getTrans(t);

    if (pP && pT) pT->addArcOut(pP);
}

void Net::addArcIn(string p, string t) {
    Place* pP = getPlace(p);
    Transition* pT = getTrans(t);

    if (pP && pT) pT->addArcIn(pP);
}

void Net::addArc(string sou, string des) {
    bool isIn = sou[0] == 'p' ? 1 : 0;
    if (isIn) addArcIn(sou, des);
    else {
        addArcOut(sou, des);
    }
}

int* Net::getMarking() {
    int* M = new int[this->nP];
    for (int i = 0; i < nP; i++) {
        M[i] = this->p[i]->getToken();
    }

    return M;
}

void Net::changeStage(int problem) {
    toString(problem);
    while (true) {
        int input;
        int i = 0;
        bool c = 0;
        string eT = "";
        for (i = 0; i < this->nT; i++) {
            if (t[i]->isEnabled()) {
                c = true;
                eT += t[i]->name.substr(1, t[i]->name.length() - 1) + "[" + to_string(i) + "], ";
            }
        }
        if (!c) {
            cout << "DEADLOCK" << endl;
            break;
        }
        eT += "Exit[-1]";
        cout << "Input option " << eT << ": ";

        cin >> input;
        if (input < t.size() && input >= 0 && t[input]->isEnabled()) {
            t[input]->firing();
            toString(problem);
            continue;
        }
        else if (input == -1) {
            break;
        }
        else {
            cout << "Transition can not be enabled" << endl;
            break;
        }
    }
}

string Net::toString(int problem) {

    switch (problem) {
    case 1: {
        //(Free(3))--->[End]--->(Doc(0))
        //   |                     ^
        //   v                     |
        //[start]--->(busy(0))-->[Change]
        cout << endl;
        int i = 0;
        cout << setw(6) << " ";
        p[i++]->print();
        cout << "<---";
        this->getTrans("tEnd")->print();
        cout << "<---";
        p[i++]->print();
        cout << endl;
        //
        cout << setw(8) << "|" << setw(27) << "^" << endl;
        cout << setw(8) << "v" << setw(27) << "|" << endl;
        cout << setw(7);
        //
        this->getTrans("tStart")->print();
        cout << "--->";
        p[i++]->print();
        cout << "-->";
        this->getTrans("tChange")->print();
        cout << endl
             << endl;
        break;
    }

    case 2: {
        cout << endl;
        cout << setw(8) << " ";
        vector<Place*>::iterator it = p.begin();
        (*it++)->print();
        cout << "-->";
        this->getTrans("tStart")->print();
        cout << "-->";
        (*it++)->print();
        cout << "-->";
        this->getTrans("tChange")->print();
        cout << "-->";
        (*it++)->print();
        cout << endl
             << endl;

        break;
    }
        //(wait(0))--->[start]--->(inside(0))--->[change]--->(done(0))
    case 3: {
        vector<Place*>::iterator it;
        it = p.begin();
        cout << setw(22);
        this->getPlace("pFree")->print();
        cout << "<----";
        this->getTrans("tEnd")->print();
        cout << "<-----";
        this->getPlace("pDocu")->print();
        cout << endl;
        //
        cout << setw(23) << '|' << setw(31) << '^';
        cout << endl;
        cout << setw(23) << 'v' << setw(31) << '|';
        cout << endl;
        //
        cout << setw(7);
        this->getPlace("pWait")->print();
        cout << "-->";
        this->getTrans("tStart")->print();
        cout << "------>";
        this->getPlace("pInside")->print();
        cout << "------>";
        this->getTrans("tChange")->print();
        cout << "---->";
        this->getPlace("pDone")->print();
        cout << endl;
        //
        cout << setw(23) << '|' << setw(31) << '^';
        cout << endl;
        cout << setw(23) << '|' << setw(31) << '|';
        cout << endl;
        //
        cout << setw(33);
        cout << "+----------";
        this->getPlace("pBusy")->print();
        cout << "-----------+";
        cout << endl<<endl;

        break;
    }
        //               +--------(Free(0))<-------+
        //               |                         |
        //               v                         |
        //(wait(4))--->[start]---->(inside(3))---->[End]--->(done(4))
        //                |                         ^
        //                v                         |
        //              (busy(1))--->[Change]--->(Doc(2))

        // wait inside done, free, busy, doc
    default:
        break;
    }
    // string res = "[";
    // for (auto it = p.begin(); it != p.end(); ++it) {
    //     res += (*it)->name.substr(1) + "(" + to_string((*it)->getToken()) + "), ";
    // }            //ten                           //number token
    // res = res.length() ? res.substr(0, res.length() - 2) : res;
    // res += "]";
    // return res;
    return " ";
}

// Nam
void Net::addPlaces(string* places, int nP) {
    // addPlace
    // input places = {p1, p2, p3, p4};
    int token = 0;
    for (int i = 0; i < nP; i++) {
        p.push_back(new Place(places[i], token));
    }

    this->nP += nP;
}

// Thu
void Net::addTransitions(string* trans, int nT) {
    // addTransition
    for (int i = 0; i < nT; i++) {
        t.push_back(new Transition(trans[i]));
    }

    this->nT += nT;
}

// Phong
void Net::addArcs(string* arcs, int nA) {
    // addArcs
    // input arcs = {"p1->t0", "t0->p2"}
    for (int i = 0; i < nA; i++) {
        string in = arcs[i].substr(0, arcs[i].find('-'));
        string out = arcs[i].substr(arcs[i].find('>') + 1);
        addArc(in, out);
    }
    return;
}

// Hung
void Net::initial(int* marking, int nP) {
    // input marking = {1, 0, 1, 0, 0}, nP = 4
    // viet them setToken o class place
    for (int i = 0; i < nP; i++) {
        p[i]->setToken(marking[i]);
    }
}

string Net::getPlaces() {
    string res = "Places: ";
    for (auto it = p.begin(); it != p.end(); ++it) {
        res += (*it)->name.substr(1) + ", ";
    }
    res = res.length() ? res.substr(0, res.length() - 2) : res;
    return res;
}

string Net::getTransitions() {
    string res = "Transitions: ";
    for (auto it = t.begin(); it != t.end(); ++it) {
        res += (*it)->name.substr(1) + ", ";
    }
    res = res.length() ? res.substr(0, res.length() - 2) : res;
    return res;
}

int* Net::setInitialM(int problem) {
    toString(problem);
    int* arr = new int[nP];
    for (int i = 0; i < nP; i++) {
        cout << "Enter number of tokens at place " << p[i]->name.substr(1) << ": ";
        int tokens = 0;
        cin >> tokens;
        p[i]->setToken(tokens);
        this->toString(problem);
    }
    return arr;
}