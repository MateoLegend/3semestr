#include <iostream>
#include <cstring>

class Media{
public:
    Media(const std::string& _filename) : filename(_filename){}
    virtual ~Media(){}

    const std::string& getFilename() const{
        return filename;
    }

    virtual void play() = 0;
    virtual void pause() = 0;
private:
    std::string filename;
};

class AudioPlayer : virtual public Media{
public:
    AudioPlayer(const std::string& _filename) : Media(_filename){}
    ~AudioPlayer(){}

    virtual void play() override {
        std::cout << "AudioPlayer: playing: " << getFilename() << std::endl;
    }
    virtual void pause() override {
        std::cout << "AudioPlayer: pausing: " << getFilename() << std::endl;
    }
    void setVolume();
};

class VideoPlayer : virtual public Media{
public:
    VideoPlayer(const std::string& _filename) : Media(_filename){}
    ~VideoPlayer(){}

    virtual void play() override {
        std::cout << "VideoPlayer: playing: " << getFilename() << std::endl;
    }
    virtual void pause() override {
        std::cout << "VideoPlayer: pausing: " << getFilename() << std::endl;
    }
    void setBrightness();
};

class AVPlayer : public VideoPlayer, public AudioPlayer{
public:
    AVPlayer(const std::string& _filename) : VideoPlayer(_filename), AudioPlayer(_filename), Media(_filename){}
    ~AVPlayer(){}

    void play(){
        std::cout << "AVPlayer: synchronizing a/v: " << getFilename() << std::endl;
        AudioPlayer::play();
        VideoPlayer::play();
    }
    void pause(){
        std::cout << "AVPlayer: pausing: " << getFilename()  << std::endl;
        AudioPlayer::pause();
        VideoPlayer::pause();
    }
};


int main(){
    AVPlayer nazwa("main.cpp");

    nazwa.play();
    nazwa.pause();


    return 0;
}