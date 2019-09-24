#ifndef CLASSX_H
#define CLASSX_H


class ClassX
{
    public:
        ClassX(int i); //some user define type
        ClassX(); //default constructor
        ClassX(const ClassX&);// copy constructor
        ClassX(ClassX&&);// move constructor
        ClassX& operator=(const ClassX&); // copy assignment: clean up target and copy
        ClassX& operator=(ClassX&&);      // move assignment: clean up target and move
        virtual ~ClassX();

    protected:

    private:
};
/*
There are five situations in which an object can be copied or moved:
As the source of an assignment
As an object initializer
As a function argument
As a function return value
As an exception

An assignment uses a copy or move assignment operator.
In principle, the other cases use a copy or move constructor.
If you are explicit about some defaults, other default definitions will not be generated.
A good rule of thumb (sometimes called the rule of zero)
is to either define all of the essential operations or none (using the default for all).
*/

//baes class no copy
class BaseShape
{
public:
    BaseShape(const BaseShape&) =delete;            // no copy operations
    BaseShape& operator=(const BaseShape&) =delete; // no copy assignments
    virtual void Draw() =0;
    explicit BaseShape(int i); //no implicit conversion from int to Vector
    //otherwise i number of baseshape is generated(should be vector,use baseshape for simple)
};
#endif // CLASSX_H
