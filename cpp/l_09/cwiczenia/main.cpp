#include <iostream>

template <typename T>

class Container{
public:
    Container(){}

    virtual ~Container(){
    //    clear();
    }

    virtual void push(const T &value) = 0;

    virtual T pop() = 0;

    virtual bool isEmpty() const = 0;

    virtual size_t size() const = 0;

};

template <typename T>
class Node {
public:
    Node(T value) : data(value), next(nullptr) {}
    T data;
    Node<T> *next;
};

// template <typename T>

// class Queue : public Container{
// public:
//     Queue(T *_head, T *_tail, size_t _currentValue) : head(_head), tail(_tail), currentValue(_currentValue){}

//     void push(const T &value) override{
//             new Node<T> *n = new Node<T>(value);
//             n->next = head;
//             head = n;
//         }

//     virtual T pop() override{

//     }

//     virtual bool isEmpty() const override{

//     }

//     virtual size_t size() const override{

//     }


// private:
//     Node<T> *head;
//     Node<T> *tail;
//     size_t currentValue;
// };

template <typename T>

class Stack : public Container<T>{
public:
    Stack(){}

    void push(const T &value) override{
        Node<T> *n = new Node<T>(value);
        n->next = head;
        head = n;
    }

    virtual T pop() override{
        Node<T> *n = head;
        T ret = n-> data;
        head = n -> next;
        delete n;
        return ret;
    }

    virtual bool isEmpty() const override{
        return false;
    }

    virtual size_t size() const override{
        return 0;
    }

private:
    Node<T> *head;
    size_t currentValue;
};




int main(){
    Stack<int> stos;
    stos.push(2);
    stos.pop();

    return 0;
}