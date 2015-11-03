#include <iosfwd>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

enum class Operation {
    INSERT, ERASE
};

class Order {

public:

    Order(long long int timestamp, const Operation &operation, int id, std::string &price)
            : timestamp(timestamp), operation(operation), id(id), price(price) { }

    Order() { }

    long long int getTimestamp() const {
        return timestamp;
    }

    const Operation &getOperation() const {
        return operation;
    }

    int getId() const {
        return id;
    }

    std::string getPrice() const {
        return price;
    }

private:
    long long int timestamp;
    Operation operation;
    int id;
    std::string price;
};

struct priceComparator {
    bool operator()(const std::string &price1, const std::string &price2) const {
        return std::stod(price1) < std::stod(price2);
    }
};

class OrderBook {

public:

    void insert(Order &order) {
        prices[order.getPrice()] += 1;
        orders.insert(std::pair<int, Order>(order.getId(), order));
    }

    double getHighestPrice() const {
        if (prices.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return std::stod(prices.rbegin()->first);
    }

    void erase(int orderId) {
        std::string price = orders[orderId].getPrice();
        prices[price] -= 1;
        if (prices[price] == 0) {
            prices.erase(price);
        }
        orders.erase(orderId);
    }

    void manageOrder(Order &currentOrder) {
        if (currentOrder.getOperation() == Operation::INSERT) {
            this->insert(currentOrder);
        } else {
            this->erase(currentOrder.getId());
        }
    }

private:
    std::map<int, Order> orders;
    std::map<std::string, int, priceComparator> prices;
    // prices stored as strings, to avoid keeping doubles as keys
};

Order processLine(std::string &line) {

    std::vector<std::string> order;
    std::string emptyString("");
    boost::split(order, line, boost::is_any_of(" "), boost::token_compress_on);
    if (order[1] == "I") {
        return Order(std::stoll(order[0]), Operation::INSERT, std::stoi(order[2]), order[3]);
    }
    return Order(std::stoll(order[0]), Operation::ERASE, std::stoi(order[2]), emptyString);

}

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("usage: %s filename\n\n", argv[0]);
        return 0;
    }
    std::ifstream file(argv[1]);
    std::string line;

    getline(file, line);
    if (line.empty()) {
        std::cout << "No orders" << std::endl;
        return 1;
    }

    int weightSum = 0;
    int highestPrice, prevTimestamp;

    OrderBook orderBook = OrderBook();
    Order currentOrder = processLine(line);
    orderBook.manageOrder(currentOrder);

    int firstTimestamp = currentOrder.getTimestamp();

    while (getline(file, line)) {

        highestPrice = orderBook.getHighestPrice();
        prevTimestamp = currentOrder.getTimestamp();

        currentOrder = processLine(line);
        orderBook.manageOrder(currentOrder);

        weightSum += (currentOrder.getTimestamp() - prevTimestamp) * highestPrice;
    }
    std::cout << weightSum / static_cast<double>(currentOrder.getTimestamp() - firstTimestamp);
    return 0;
}