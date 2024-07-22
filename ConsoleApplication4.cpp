#include <iostream>
#include <sstream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>

// Функция гет-запроса и получения списка пользователей
void performGetRequest() {
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        std::string url = "https://jsonplaceholder.typicode.com/users";
        request.setOpt(new curlpp::options::Url(url));

        std::ostringstream response;
        request.setOpt(new curlpp::options::WriteStream(&response));

        request.perform();

        nlohmann::json users = nlohmann::json::parse(response.str());

        for (const auto& user : users) {
            std::cout << "ID: " << user["id"] << "\n";
            std::cout << "Name: " << user["name"] << "\n";
            std::cout << "Email: " << user["email"] << "\n";
            std::cout << "-------------------\n";
        }

    }
    catch (curlpp::RuntimeError& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (curlpp::LogicError& e) {
        std::cerr << "Logic error: " << e.what() << std::endl;
    }
}

// Функция пост-запроса, создания нового пользователя
void performPostRequest() {
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        std::string url = "https://jsonplaceholder.typicode.com/users";
        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::Post(true));

        nlohmann::json newUser = {
            {"name", "Ivanov Ivan"},
            {"username", "vanek2000"},
            {"email", "ivanivanov2000@gmail.com"}
        };

        std::string requestBody = newUser.dump();
        request.setOpt(new curlpp::options::PostFields(requestBody));
        request.setOpt(new curlpp::options::PostFieldSize(requestBody.size()));

        std::ostringstream response;
        request.setOpt(new curlpp::options::WriteStream(&response));

        request.perform();

        std::cout << "Post request:\nResponse: " << response.str() << std::endl;

    }
    catch (curlpp::RuntimeError& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (curlpp::LogicError& e) {
        std::cerr << "Logic error: " << e.what() << std::endl;
    }
}

// Функция put-запроса и обновления данных пользователя
void performPutRequest(int userId) {
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        std::string url = "https://jsonplaceholder.typicode.com/users/" + std::to_string(userId);
        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::CustomRequest{ "PUT" });

        nlohmann::json updatedUser = {
            {"name", "NeIvanov NeIvan"},
            {"username", "NeVanek1999"},
            {"email", "NeIvanNeIvanov1999@gmail.com"}
        };

        std::string requestBody = updatedUser.dump();
        request.setOpt(new curlpp::options::PostFields(requestBody));
        request.setOpt(new curlpp::options::PostFieldSize(requestBody.size()));

        std::ostringstream response;
        request.setOpt(new curlpp::options::WriteStream(&response));

        request.perform();

        std::cout << "Put request:\nResponse: " << response.str() << std::endl;

    }
    catch (curlpp::RuntimeError& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (curlpp::LogicError& e) {
        std::cerr << "Logic error: " << e.what() << std::endl;
    }
}

// Функция delete-запроса и удаления пользователя
void performDeleteRequest(int userId) {
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        std::string url = "https://jsonplaceholder.typicode.com/users/" + std::to_string(userId);
        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::CustomRequest{ "DELETE" });

        std::ostringstream response;
        request.setOpt(new curlpp::options::WriteStream(&response));

        request.perform();

        std::cout << "Delete request:\nResponse: " << response.str() << std::endl;

    }
    catch (curlpp::RuntimeError& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (curlpp::LogicError& e) {
        std::cerr << "Logic error: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "GET Request:\n";
    performGetRequest();

    std::cout << "\nPOST Request:\n";
    performPostRequest();

    std::cout << "\nPUT Request:\n";
    performPutRequest(1);

    std::cout << "\nDELETE Request:\n";
    performDeleteRequest(1);

    std::cin.get();

    return 0;
}
