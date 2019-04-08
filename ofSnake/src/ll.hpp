#include <utility>
#include <cassert>
#include "ll.h"

using namespace cs126linkedlist;

template<typename ElementType>
LinkedList<ElementType>::LinkedList() {
    // Do nothing
}

template<typename ElementType>
LinkedList<ElementType>::LinkedList(const std::vector<ElementType> &values) {
    if (values.empty()) {
        return;
    }
    
    LinkedListNode *node = new LinkedListNode;
    linked_list_size = 0;
    
    for (int i = 0; i < values.size(); ++i) {
        if (i != 0) {
            node->next = new LinkedListNode;
            node = node->next;
        }
        
        node->value = values.at(i);
        linked_list_size++;
    }
    
    head = node;
    delete node;
}

// Copy constructor
template<typename ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList<ElementType>& source) {
    if (source.linked_list_size == 0) {
        return;
    }
    
    head = new LinkedListNode();
    LinkedListNode *original_node = (source).head;
    LinkedListNode *copy_node = new LinkedListNode();
    linked_list_size = 1;
    
    while (linked_list_size < source.linked_list_size) {
        copy_node->value = original_node->value;
        original_node = original_node->next;
        copy_node->next = new LinkedListNode();
        copy_node = copy_node->next;
        linked_list_size++;
    }
}

// Move constructor
template<typename ElementType>cs126linkedlist::LinkedList<ElementType>::LinkedList(LinkedList<ElementType>&& source) noexcept {
    head = source.head;
    linked_list_size = source.linked_list_size;
}

// Destructor
template<typename ElementType>
LinkedList<ElementType>::~LinkedList() {
    clear();
    linked_list_size = 0;
}

// Copy assignment operator
template<typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator= (const LinkedList<ElementType>& source) {
    
}

// Move assignment operator
template<typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator= (LinkedList<ElementType>&& source) noexcept {

}

template<typename ElementType>
void LinkedList<ElementType>::push_front(ElementType value) {
    LinkedListNode *node = new LinkedListNode();
    node->value = value;
    node->next = head;
    head = node;
    linked_list_size++;
}

template<typename ElementType>
void LinkedList<ElementType>::push_back(ElementType value) {
    if (empty()) {
        head = new LinkedListNode();
        head->value = value;
        head->next = nullptr;
        linked_list_size++;
        return;
    }
    
    LinkedListNode *node = head;
    int count = 0;
    
    while (count < linked_list_size - 1) {
        node = node->next;
        count++;
    }
    
    node->next = new LinkedListNode();
    node->next->value = value;
    linked_list_size++;
}

template<typename ElementType>
ElementType LinkedList<ElementType>::front() const{
    assert(linked_list_size != 0);
    return head->value;
}

template<typename ElementType>
ElementType LinkedList<ElementType>::back() const {
    assert(linked_list_size != 0);
    LinkedListNode *node = head;
    
    while (node->next != nullptr) {
        node = node->next;
    }
    
    return node->value;
}

template<typename ElementType>
void LinkedList<ElementType>::pop_front() {
    if (linked_list_size == 0) {
        return;
    }
    
    if (linked_list_size == 1) {
        head = nullptr;
        linked_list_size--;
    } else {
        LinkedListNode *node = head;
        head = head->next;
        linked_list_size--;
        node = nullptr;
    }
}

template<typename ElementType>
void LinkedList<ElementType>::pop_back() {
    if (head == nullptr) {
        return;
    }
    
    LinkedListNode *node = head;
    
    while (node->next != nullptr) {
        node = node->next;
    }
    
    linked_list_size--;
    
    delete node->next;
    node->next = nullptr;
}

template<typename ElementType>
int LinkedList<ElementType>::size() const {
    return linked_list_size;
}

template<typename ElementType>
bool LinkedList<ElementType>::empty() const {
    return linked_list_size == 0;
}

template<typename ElementType>
void LinkedList<ElementType>::clear() {
    while (linked_list_size != 0) {
        pop_front();
    }
}

template<typename ElementType>
std::ostream& operator<<(std::ostream& os, const LinkedList<ElementType>& list) {
    if (list.empty()) {
        return os;
    }
    
    auto iterator = list.begin();
    
    while (iterator != list.end()) {
        os << *iterator + ", ";
        ++iterator;
    }
    
    os << *iterator;
    return os;
}

template<typename ElementType>
void LinkedList<ElementType>::RemoveNth(int n) {
    LinkedListNode *node = head;
    
    for (int i = 0; i < n - 1; ++i) {
        node = node->next;
    }
    
    LinkedListNode *deleteNode = node->next;
    node->next = deleteNode->next;
    head = node;
    linked_list_size--;
    
    delete deleteNode, node;
}

template<typename ElementType>
void LinkedList<ElementType>::RemoveOdd() {
    if (empty()) {
        return;
    }
    
    int new_size;
    if (linked_list_size % 2 == 1) {
        new_size = (linked_list_size - 1) / 2;
    } else {
        new_size = linked_list_size / 2;
    }
    
    LinkedListNode *node = head;
    
    while (linked_list_size > new_size) {
        node->next = node->next->next;
        node = node->next;
        linked_list_size--;
    }
    
    linked_list_size = new_size;
}

template<typename ElementType>
bool LinkedList<ElementType>::operator==(const LinkedList<ElementType> &rhs) const {
    LinkedListNode *left = head;
    LinkedListNode *right = rhs.head;
    
    if (linked_list_size != rhs.linked_list_size) {
        return false;
    }
    
    for (int i = 0; i < linked_list_size; ++i) {
        if (left->value != right->value) {
            return false;
        }
    }
    
    return true;
}

template<typename ElementType>
bool operator!=(const LinkedList<ElementType>& lhs, const LinkedList<ElementType> &rhs) {
    return !(lhs == rhs);
}

template<typename ElementType>
typename LinkedList<ElementType>::iterator& LinkedList<ElementType>::iterator::operator++() {
    if (current_) {
        current_ = current_->next;
    }
    
    return *this;
}

template<typename ElementType>
ElementType& LinkedList<ElementType>::iterator::operator*() const {
    return current_->value;
}

template<typename ElementType>
bool LinkedList<ElementType>::iterator::operator!=(const LinkedList<ElementType>::iterator& other) const {
        return current_ != other.current_;
}

template<typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::begin() {
    return iterator(head);
}

template<typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::end() {
    LinkedListNode *node = head;
    int count = 0;
    
    while (count < linked_list_size) {
        node = node->next;
        count++;
    }
    
    return iterator(node);
}

template<typename ElementType>
typename LinkedList<ElementType>::const_iterator& LinkedList<ElementType>::const_iterator::operator++() {
    if (current_) {
        current_ = current_->next;
    }
    
    return *this;
}

template<typename ElementType>
const ElementType& LinkedList<ElementType>::const_iterator::operator*() const {
    return current_->value;
}

template<typename ElementType>
bool LinkedList<ElementType>::const_iterator::operator!=(const LinkedList<ElementType>::const_iterator& other) const {
        return current_ != other.current_;
}

template<typename ElementType>
typename LinkedList<ElementType>::const_iterator LinkedList<ElementType>::begin() const {
    return head;
}

template<typename ElementType>
typename LinkedList<ElementType>::const_iterator LinkedList<ElementType>::end() const {
    LinkedListNode *node = head;
    int count = 0;
    
    while (count + 1 < linked_list_size) {
        node = node->next;
        count++;
    }
    
    return const_iterator(node);
}
