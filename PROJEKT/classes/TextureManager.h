#ifndef TEXTUREH
#define TEXTUREH
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>

//Singleton made to manage all the textures
class TextureManager : public sf::Texture{
private:
    TextureManager(string path){
        loadFromFile(path);       
    }
public:
    static TextureManager & getTextureStone(){
        static TextureManager t("./assets/Rock.png");
        return t;
    }
    static TextureManager & getTextureDirt(){
        static TextureManager t("./assets/Dirt.png");
        return t;
    }
    static TextureManager & getTextureBedrock(){
        static TextureManager t("./assets/Bedrock.png");
        return t;
    }
    static TextureManager & getTexturePlayer(){
        static TextureManager t("./assets/charscaled.png");
        return t;
    }
    static TextureManager & getPushTexture(){
        static TextureManager t("./assets/charpush.png");
        return t;
    }
    static TextureManager & getTextureChest(){
        static TextureManager t("./assets/chest.png");
        return t;
    }
    static TextureManager & getTextureDiamond(){
        static TextureManager t("./assets/Diamond.png");
        return t;
    }
    static TextureManager & getTextureDeath(){
        static TextureManager t("./assets/grave.png");
        return t;
    }
    static TextureManager & getTextureLava(){
        static TextureManager t("./assets/lava.png");
        return t;
    }
    static TextureManager & getBackgroundTexture(){
        static TextureManager t("./assets/back_cave.png");
        t.setRepeated(true);
        return t;
    }
};
#endif
