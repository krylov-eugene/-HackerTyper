#include <SFML/Graphics.hpp>
#include <fstream>

#include <iostream>

class DrawableObject {
    public:

    virtual void Draw(){

    }
   
};
class GraphicManager{
    public:

        ~GraphicManager(){
            for(int i = 0;i< number_of_objects;++i){
                delete[] objects[i];
            }

            delete[] objects;
        }
        

        void DrawAll(){

            for(int i = 0 ;i<number_of_objects;++i){
                
                (*(objects[i])).Draw();
                
            }
        }
        void Register(DrawableObject* object,int number_of_input_object){
            objects[number_of_input_object] = object;
            
        }
        void SetNumberOfObjectsAndDoArray(int number_of_objects_input){
            number_of_objects = number_of_objects_input;
            objects = new DrawableObject*[number_of_objects];
        }
        
    private:
        int number_of_objects ;
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
class txt:public DrawableObject {
    public:
        ~txt(){

            delete[] txt;
            delete[] text;
            delete[] window;
        }

        void Draw(){

            (*text).setString(txt);
            (*window).clear();
            (*window).draw((*text));
            (*window).display();

        }
        void SetTxt(char* txt_input){
            txt = txt_input;
        }


        sf::RenderWindow* window;
        sf::Text* text;
    private:
    
        char* txt;
};

void RecalculateArray(char* txt,char* words,int& TXT_COUNTER,int& WORD_COUNTER){

    words[WORD_COUNTER]=txt[TXT_COUNTER];
    TXT_COUNTER++;WORD_COUNTER++;
    words[WORD_COUNTER]=txt[TXT_COUNTER];
    TXT_COUNTER++;WORD_COUNTER++;
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
void DrawAll(class GraphicManager&  manager ){

    manager.DrawAll();

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
    setlocale(LC_ALL,"Rus");

    sf::RenderWindow window(sf::VideoMode(1500,1000),".");
    window.setKeyRepeatEnabled(false);
    //class Window Window;
    //Window.SetWindow(&window);

    int size_of_txt = 0;
    char* txt = ReadFromFile(size_of_txt,"abc.txt");
    char* words = new char[size_of_txt];
    class txt Word;
    Word.SetTxt(words); 
    
    
    
    sf::Font font;
    if ( !font.loadFromFile( "Arial.ttf" ) ){
    
        return 0 ;
    }

    
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Green);
    //class Text Text;
    //Text.text=&text;
    Word.text = &text;
    Word.window = &window;

    class GraphicManager manager;
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
        
        DrawAll(manager);
    }

 delete []txt;
 delete []words;
 return 0;
