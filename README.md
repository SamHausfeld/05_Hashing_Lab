05_Hashing_Lab
==============

Implement a hash table in C++

Requirements
------------

1. `keyExists`, `find`, `remove`, and `size` should all be O(1)
2. `add` should be reasonably fast. Use linear probing to find an open slot in the hash table. This will be O(1), on average, except when `grow` is called.
3. `grow` should be O(n)
4. Do not leak memory


Reading
=======
"Open Data Structures," Chapter 5, except for 5.2.3. http://opendatastructures.org/ods-cpp/5_Hash_Tables.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. Of course.  Size is a simple return so it only takes O(1) to begin with, and the rest of the methods are mathematically probable to come out to O(1) .
2. Should be operable, however this was the method with which I had the most trouble.
3. Confusing method as well, needed a lot of help.  Should be working smoothly though.
4. Deletes when neccesarry.

#### 2. I decided to use two function (`keyExists` and `find`) to enable lookup of keys. Another option would have been to have `find` return a `T*`, which would be `NULL` if an item with matching key is not found. Which design do you think would be better? Explain your reasoning. You may notice that the designers of C++ made the same decision I did when they designed http://www.cplusplus.com/reference/unordered_map/unordered_map/

I think the design chosen would be best, it's always useful to make helper methods.  They make the rest of the code easier to read, and probably cut down on time too, if I had to guess.

#### 3. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

I had a lot of trouble transferring my notes from the book into application during the lab.  This was a challenging assignment, and I wish I had started it sooner.