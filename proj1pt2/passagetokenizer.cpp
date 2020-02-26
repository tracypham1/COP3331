#include "passagetokenizer.h"

PassageToken::PassageToken() : name(" "), text(" ") { /*...*/ }

//PassageTokenizer stuff
PassageTokenizer::PassageTokenizer(string t) : text(t), nextPt(true), firstCommand(true) { /*...*/ }

//similiar to storytokenizer
PartToken PassageTokenizer::nextPart(){
    //create a PartToken obj to return,
    PartToken part;
    string line(text); //holds "(set: $debug to false)(set: ... [[log onto Facebook]], or [[watch Netflix]]?"

    string te(""); 
    int i;
  
    switch(line.at(0)){
        case '(': //when its a command
            if(line.at(1) == 's')
                part.setType(SET);
            else if(line.at(1) == 'g')
                part.setType(GOTO);
            else if(line.at(1) == 'i')
                part.setType(IF);
            else if((line.at(1) == 'e') && (line.at(0+5) == '-'))
                part.setType(ELSEIF);
            else
                part.setType(ELSE);      

            //all five commands formatted same so use dame conditon for loop
            for(i = 0; line.at(i) != ')'; i++)
                te += line.at(i);
            te += line.at(i++); //add that ')' to the text
            break;
        case '[': //when its a block of link
            if(line.at(1) == '['){
                part.setType(LINK);
                for(i = 0; line.at(i) != ']'; i++)
                    te += line.at(i);
                te += line.at(i++);
                te += line.at(i++);
            }
            else{
                part.setType(BLOCK);
                for(i = 0; line.at(i) != ']'; i++){
                    int j;
                    te += line.at(i);
                    
                    //if '[' is found, ignore the first 
                    if(line.at(i+1) == '['){
                        for(j = i+1; line.at(j) != ']'; j++)
                            te += line.at(j);
                        te += line.at(j);
                        i = j; // i++ once we leave this if
                    }
                }
                te += line.at(i);
                i++;

                //when block is the last line
                if(i == line.length())
                    nextPt = false;
            }
            break;
        default: //when its just text
            part.setType(TEXT);

            for(i = 0; (line.at(i) != '(') && (line.at(i) != '['); i++){ //text is not allowed to have '(' or '['
                te += line.at(i);
                if(i+1 == line.length()){
                    nextPt = false;
                    break;
                }           
            }
            break;
        }//end switch

    part.setText(te); //set that PartToken object text as this part extracted

    //if there is a next part, remove this part from the line
    if(nextPt == true)
        text = line.substr(i); //redefine line aka text in PassageTokenizer
  
    return part;

}
//im such an idiot that didn't know what PassagToken text held


/***************** writing PartToken stuff in here for now *************************/
PartToken::PartToken(string tx, toktype_t tp) : text(tx), type(tp) { /*...*/ }
