// Provided by:   Cynthia Carter
// Lab:           Sequence and dynamic Memory
// FILE: sequence.cpp
// CLASS PROVIDED: sequence (part of the namespace main_savitch_4)
#include "sequence.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;
 
namespace main_savitch_4 {
    
    // CONSTRUCTOR
    // Postcondition: The sequence has been initialized as an empty sequence.
    // The insert/attach functions will work efficiently (without allocating
    // new memory) until this capacity is reached.
    sequence::sequence (size_type initial_capacity) 
    {
        // reseting values (creating an empty sequance that can be intilized)
        data_ = new value_type[initial_capacity];
        capacity_ = initial_capacity;
        current_index_ = 0;
        used_ = 0;
    }
    
    
    // COPY CONSTRUCTOR
    // Postcondition: The sequence has been initialized to the sequence
    //   passed in.
    // The insert/attach functions will work efficiently (without allocating
    // new memory) until the source's capacity is reached.
    sequence::sequence(const sequence& source) 
    {
        data_ = new value_type [source.capacity_];
        capacity_ = source.capacity_;
        current_index_ = source.current_index_;
        used_ = source.used_;
        std::copy(source.data_, source.data_ + source.used_, data_);
    }
    
    
    // DESTRUCTOR
    // Postcondition: The memory allocated for the object has been released.
    sequence::~sequence() 
    {
        delete [] data_;
    }
    
    
    // ----- MODIFICATION MEMBER FUNCTIONS ----- //
        
    // Postcondition: The sequence's current capacity is changed to the 
    //   new_capacity (but not less that the number of items already on the
    //   list). The insert/attach functions will work efficiently (without
    //   allocating new memory) until this new capacity is reached.
    void sequence::resize(size_type new_capacity)
   {
       value_type * p;
       
       if (new_capacity == capacity_)
       {
           return;
       }
       else if (capacity_ < new_capacity)
       {
       p = new value_type[new_capacity];
       std::copy(data_, data_ + used_, p);
       delete [] data_;
       data_ = p;
       capacity_ = new_capacity;
       }
   }
   
    // Postcondition: The first item on the sequence becomes the current item
    //   (but if the sequence is empty, then there is no current item).
    void sequence::start( ) 
    {
        current_index_ = 0;
    }
    
    // Precondition: is_item returns true.
    // Postcondition: If the current item was already the last item in the
    //   sequence, then there is no longer any current item. Otherwise, the new
    //   current item is the item immediately after the original current item.
    void sequence::advance() 
    {
        if (is_item() == true) 
        {
            current_index_++;
        }
        else 
        {
            return;
        }
    }
        
    // HELPER (PRIVATE) FUNCTIONS

    // Precondition: The capacity is (at least one) bigger than the number of
    //   items stored.
    // Postcondition: All data items from index to the number of items stored
    //   will be moved down one space.
    void sequence::move_down(size_type index)
    {
         for (size_type count = current_index_; count <= used_; count++)
        {
            data_[count] = data_[count + 1];
        }
    }

    // Precondition: There is at least one item stored.
    // Postcondition: All data items from index to the number of items stored
    //   will be moved up one space.
    void sequence::move_up(size_type index)
    {
        for (size_type count = used_; count > current_index_; count--)
        {
            data_[count] = data_[count - 1];
        }
    }
        
    //   Postcondition: A new copy of entry has been inserted in the sequence
    //   before the current item. If there was no current item, then the new
    //   entry has been inserted at the front of the sequence. In either case,
    //   the newly inserted item is now the current item of the sequence.
    void sequence::insert(const value_type& entry) 
    {
        size_type zero_ = 0;
        if (size() == zero_)
        {
            data_[0] = entry;
            current_index_ = zero_;
            used_++;
        }
        else if (capacity_ == used_)
        {
            resize(sequence::capacity_ + 1);
            move_up(current_index_);
            data_[current_index_] = entry;
            used_++;
        }
        else if (is_item() == false)
        {
            start();
            move_up(current_index_);
            data_[current_index_] = entry;
            used_++;
        }
        else
        {
            move_up(current_index_);
            data_[current_index_] = entry;
            used_++;
        }
    }
        
     // Postcondition: A new copy of entry has been inserted in the sequence
    //   after the current item. If there was no current item, then the new
    //   entry has been attached to the end of the sequence. In either case,
    //   the newly inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry) 
    {
        
        size_type zero_ = 0;
        if (size() == zero_)
        {
            data_[0] = entry;
            used_++;
            current_index_ = zero_;
        }
        else if (is_item() == false)
        {
            current_index_ = size() - 1;
            if (size() == capacity_)
            {
                resize(capacity_ + 1);
            }
            advance();
            data_[current_index_] = entry;
            used_++;
        }
        else if (current_index_ == used_ - 1)
        {
            if (size() == capacity_)
            {
                resize(capacity_ + 1);
            }
            advance();
            data_[current_index_] = entry;
            used_++;
        }
        else
        {
            advance();
            move_up(current_index_);
            data_[current_index_] = entry;
            used_++;
        }
    }
        
    // Postcondition: The current item has been removed from the sequence,
    //   and the item after this (if there is one) is now the new current item.
    void sequence::remove_current( ) 
    {
        assert(is_item());
        for (size_type i = current_index_; i < used_ - 1; ++i)
        {
            data_[i] = data_[i + 1];
        }
        --used_;
    }
        
        
    // Postcondition: The current object is equivalent to the object passed
    //   in.
    void sequence::operator=(const sequence& source) {
        if (this == &source)
        {
            return;
        }
        value_type *new_data_ = new value_type [source.capacity_];
        copy(source.data_, source.data_+source.used_, new_data_);
        delete [] data_;
        data_ = new_data_;
        used_ = source.used_;
        capacity_ = source.capacity_;
        if (source.is_item())
        {
            current_index_ = source.current_index_;
        }
        else
        {
            current_index_ = used_;
        }
    }
        
        
    // ----- CONSTANT MEMBER FUNCTIONS ------ //
    
    // Postcondition: The return value is the number of items in the sequence.
    sequence::size_type sequence::size( ) const 
    {
        return used_;
    }
    
    // Postcondition: A true return value indicates that there is a valid
    //   "current" item that may be retrieved by activating the current
    //   member function (listed below). A false return value indicates that
    //   there is no valid current item.
    bool sequence::is_item( ) const 
    {
      return (current_index_ >= 0 && current_index_ < used_);
    }
    
    //  Precondition: is_item( ) returns true.
    //  Postcondition: The item returned is the current item in the sequence.
    sequence::value_type sequence::current( ) const 
    {
        assert(is_item());
        return data_[current_index_];
    }
    
    //  Postcondition: The return value is true if both sequences contain no
    //    data items. Also, if the length is greater than zero, then the
    //    sequences must contain the same number of items and the items at the
    //    same location must be equal.
     bool sequence::operator ==(const sequence& other) 
   {
        
        if ((other.size() == 0) && (size() == 0))
        {
            return true;
        }
        if ((other.size() > 0) && (size() > 0))
        {
            if (other.size() == size())
            {
                sequence copy = other;
                size_type c = current_index_;
                current_index_ = 0;
                copy.current_index_ = 0;
                
                for (unsigned int i = 0; i < size(); i++)
                {
                    copy.current_index_ = i;
                    current_index_ = i;
                    if (copy.current() != current())
                    {
                        current_index_ = c;
                        return false;
                    }
                }
            }
            
        }
        return true;
    }
    
    
    //  Postcondition: The return value is false if both sequences contain no
    //    data items. Also, if the length is greater than zero, then the
    //    sequences must not contain the same number of items or the items at
    //    the same location must not be equal.
    bool sequence::operator !=(const sequence& other) 
    {
        if ((current_index_ == 0) && (used_ == 0))
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    
}