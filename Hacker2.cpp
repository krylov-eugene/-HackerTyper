#include <SFML/Graphics.hpp>
#include <fstream>

#include <iostream>

class DrawableObject {
    public:

    virtual void Draw(){
        
        std::cout<<"Я зашел в функцию рисования в рисуемых обьектах"<<std::endl;

    }
   
};
class GraphicManager{
    public:

        ~GraphicManager(){

            delete[] objects;
        }
        

        void DrawAll(){

            for(int i = 0 ;i<number_of_objects;++i){
                std::cout<<"Я зашел в функцию рисования в график мэнэджере"<<std::endl;

                objects[i].Draw();
                std::cout<<"Я прошел одну итерацию"<<std::endl;
                
            }
        }
        void Register(DrawableObject& object,int number_of_input_object){
            objects[number_of_input_object] = object;
        }
        void SetNumberOfObjectsAndDoStorage(int number_of_objects_input){
            number_of_objects = number_of_objects_input;
            objects = new DrawableObject[number_of_objects];
        }
        DrawableObject* GetObject(int number_of_object){
            return &(objects[number_of_object]);
        }
        
    private:
        int number_of_objects ;
        DrawableObject* objects ;
        
        

};
class Window{
    public:
    void SetWindow(sf::RenderWindow* window_input){
        window = window_input;
    }

    sf::RenderWindow* window;
};
class Text{
    public:
    
    sf::Text* text;

};
class txt:public DrawableObject,public Window,public Text {
    public:
        ~txt(){

            delete[] txt;
        }

        void Draw(){
            std::cout<<"Я пытаюсь вывести массив на экран"<<std::endl;

            (*text).setString(txt);
            (*window).clear();
            (*window).draw((*text));
            (*window).display();

        }
        void SetTxt(char* txt_input){
            txt = txt_input;
        }

    private:
    
        char* txt;

};


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

            words[WORD_COUNTER]=txt[TXT_COUNTER];
            TXT_COUNTER++;WORD_COUNTER++;
            words[WORD_COUNTER]=txt[TXT_COUNTER];
            TXT_COUNTER++;WORD_COUNTER++;
            words[WORD_COUNTER]=txt[TXT_COUNTER];
            TXT_COUNTER++;WORD_COUNTER++;
            words[WORD_COUNTER]='\0';


          


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
            words[WORD_COUNTER]=txt[TXT_COUNTER];
            TXT_COUNTER++;WORD_COUNTER++;
            words[WORD_COUNTER]=txt[TXT_COUNTER];
            TXT_COUNTER++;WORD_COUNTER++;
            words[WORD_COUNTER]=txt[TXT_COUNTER];
            TXT_COUNTER++;WORD_COUNTER++;
            words[WORD_COUNTER]='\0';


           

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
    class Window Window;
    Window.SetWindow(&window);

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
    class Text Text;
    Text.text=&text;

    class GraphicManager manager;
    manager.SetNumberOfObjectsAndDoStorage(1);
    manager.Register(Word,0);


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
}
