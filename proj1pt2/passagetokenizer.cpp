#include "passagetokenizer.h"

PassageToken::PassageToken() : name(" "), text(" ") { /*...*/ }

//PassageTokenizer stuff
PassageTokenizer::PassageTokenizer(string t) : text(t), nextPt(true) { /*...*/ }

string PassageTokenizer::getText() const{

}
    
//set nextPart = true or false
PartToken PassageTokenizer::nextPart(string){

}


/***************** writing PartToken stuff in here for now *************************/
PartToken::PartToken(string tx, toktype_t tp) : text(tx), type(tp) { /*...*/ }
