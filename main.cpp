#include <iostream>
#include <string>
#include <ctime>
#include "User.h"
#include "Post.h"
#include "Comment.h"
#include "Notification.h"
#include "Relationship.h"
#include "crow_all.h"
using namespace std;

int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/api/submit").methods("POST"_method)([](const crow::request& req){
        auto json_body = crow::json::load(req.body);
        if (!json_body)
            return crow::response(400);
        std::string username = json_body["username"].s();
        crow::json::wvalue response;
        response["message"] = "Hello, " + username + " from C++!";
        return crow::response{response};
    });
    app.port(18080).multithreaded().run();

    crow::SimpleApp app;
    CROW_ROUTE(app, "/api/submit").methods("POST"_method)(
        [](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invalid JSON");
            }
            std::string username = body["username"].s();
            crow::json::wvalue res;
            res["message"] = "Received username: " + username;
            return crow::response(res);
        });
    CROW_ROUTE(app, "/<string>")
    ([](std::string filename) {
        std::ifstream file("html/" + filename);
        if (!file) return crow::response(404);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return crow::response(buffer.str());
    });
    app.port(18080).multithreaded().run();

    User u = User(1, "tempuser", "tempPW", "tempemail@gmail.com");
    Post p = Post(1, "Hello", &u);
    cout << p.getTimestamp();
}
