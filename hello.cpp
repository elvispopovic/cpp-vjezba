#include <iostream>
#include <thread>
#include <chrono>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class Hello 
{
private:
    int counter;

public:
    Hello(const std::string& address) : m_listener(address) 
    {
        m_listener.support(methods::GET, std::bind(&Hello::handle_get, this, std::placeholders::_1));
    }


    void start() 
    {
    	counter = 0;
        m_listener.open().then([this]() 
        {
            std::cout << "Slusam GET zahtjeve na: " << m_listener.uri().to_string() << std::endl;
        }).wait();
    }

    void handle_get(http_request request) 
    {
    	counter++;
        ucout << "Primljen GET zahtjev broj " << counter << "." << std::endl;
        json::value response;
        response[U("poruka")] = json::value::string(U("Hello World!"));
        response[U("zahtjev")] = json::value(counter);
        request.reply(status_codes::OK, response);
    }

private:
    http_listener m_listener;
};

int main() 
{
    const std::string address = "http://0.0.0.0:8080"; // Slušam na svim suceljima
    Hello hello(address); // Kreiram objekt hello klase Hello
    hello.start(); // pozivam start metodu objekta hello

    while (true) 
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep to prevent busy loop

    return 0;
}
