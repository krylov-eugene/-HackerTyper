#include <SFML/Graphics.hpp>
#include <fstream>


class DrawableObject {
    public:
    virtual ~DrawableObject(){}

    virtual void Draw(sf::RenderWindow* window){}

};
class GraphicManager{
    public:

        ~GraphicManager(){
            for(int i = 0;i< amount_of_objects;++i){

                //delete[] objects[i];
            }

            delete[] objects;
        }
        void DrawAll(sf::RenderWindow* window){

            for(int i = 0 ;i<amount_of_objects;++i){
                
                (*(objects[i])).Draw(window);
                
            }
        }
        void Register(DrawableObject* object,int number_of_input_object){
            objects[number_of_input_object] = object;
            
        }
        void SetNumberOfObjectsAndDoArray(int amount_of_objects_input){
            amount_of_objects = amount_of_objects_input;
            objects = new DrawableObject*[amount_of_objects];
        }
        
    private:
        int amount_of_objects ;
        DrawableObject **objects ;
};
/*class Window{
    public:
     ~Window(){

        delete[] window;
    }
    void SetWindow(sf::RenderWindow* window_input){
        window = window_input;
    }

    sf::RenderWindow* window;
}; 
class Text{
    public:
    ~Text(){

        delete[] text;
    }
    
    sf::Text* text;

};*/
class Txt:public DrawableObject {
    public:
        ~Txt(){

            delete[] txt;
            
        }
        void Draw(sf::RenderWindow* window){

            (*text).setString(txt);
            (*window).clear();
            (*window).draw((*text));
            (*window).display();

        }
        void SetTxt(char* txt_input){
            txt = txt_input;
        }
        void SetText(sf::Text* text_input){

            text=text_input;

        }

    private:
        sf::Text* text;
        char* txt;
};

void RecalculateArray(char* txt,char* words,int& TXT_COUNTER,int& WORD_COUNTER){

    words[WORD_COUNTER]=txt[TXT_COUNTER];
    TXT_COUNTER++;WORD_COUNTER++;
    words[WORD_COUNTER]='\0';
}
void RefreshWindow (char* txt,char* words,const int size_of_txt ,int& TXT_COUNTER ,int& WORD_COUNTER ,const int NUMBER_OF_LINE_TRANSFERS ,bool& IS_A_BUTTON_PRESSED){
   if(IS_A_BUTTON_PRESSED){
        int counter = 0;
        int size_of_words = 0;
            for(int i = 0;;){
                if((int)words[i]!=16 && words[i]!='\0'){
                    size_of_words++;
                    i++;
                }else{
                    break;
                }
            }
        for(int i = 0 ; i < size_of_words ; ++i ){

            if(words[i]=='\n'){
                ++counter;
            }
        }
        if(counter < NUMBER_OF_LINE_TRANSFERS){

            RecalculateArray(txt,words,TXT_COUNTER,WORD_COUNTER);

        }else{
            
            int number_of_symbols_in_the_first_string = 0;
            for(int i = 0 ;;){
                if(words[i]!='\n'){
                    number_of_symbols_in_the_first_string++;
                    i++;
                }else{
                    number_of_symbols_in_the_first_string++;
                    break;
                }
            }
            
            for(int i = 0;i<size_of_words-number_of_symbols_in_the_first_string;++i){
            
                words[i]=words[i+number_of_symbols_in_the_first_string];

            }

            WORD_COUNTER = size_of_words-number_of_symbols_in_the_first_string;
            
            RecalculateArray(txt,words,TXT_COUNTER,WORD_COUNTER);
        }

        IS_A_BUTTON_PRESSED = false;

    }
}
void DrawAll(class GraphicManager& manager ,sf::RenderWindow* window){

    manager.DrawAll(window);

}
char* ReadFromFile(int& size_of_txt,char name_of_file[]){

    std::fstream f;

    f.open(name_of_file);
    f.seekg(0,std::ios::end);
    size_of_txt = f.tellg();
    char* txt = new char[size_of_txt];
    f.seekg(0,std::ios::beg);
    f.read(txt,size_of_txt);
    f.close();

    return txt;
}

int main(){

    sf::RenderWindow window(sf::VideoMode(1500,1000),".");
    window.setKeyRepeatEnabled(false);


    int size_of_txt = 0;
    char* txt = ReadFromFile(size_of_txt,"abc.txt");
    char* words = new char[size_of_txt];
   
    
    sf::Font font;
    if ( !font.loadFromFile( "Arial.ttf" ) ){
    
        return 0 ;
    }

    
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Green);
    

    Txt Word;
    Word.SetTxt(words); 
    Word.SetText(&text);


    GraphicManager manager;
    manager.SetNumberOfObjectsAndDoArray(1);
    manager.Register(&Word,0);


    int TXT_COUNTER = 0;
    int WORD_COUNTER = 0;
    const int NUMBER_OF_LINE_TRANSFERS = 27;
    bool IS_A_BUTTON_PRESSED = false;

    while(window.isOpen()){
   
        sf::Event event;
        while(window.waitEvent(event)){

            if(event.type == sf::Event::Closed){
                window.close();
                break;
            }
            if(event.type == sf::Event::KeyPressed){

                IS_A_BUTTON_PRESSED = true;
                break;

            }   
        }

        RefreshWindow(txt,words,size_of_txt,TXT_COUNTER,WORD_COUNTER,NUMBER_OF_LINE_TRANSFERS,IS_A_BUTTON_PRESSED);
        
        DrawAll(manager,&window);
    }

 delete []txt;
 //delete []words;
 return 0;
}
