//
//  main.cpp
//  hw3
//
//  Created by 杨子鸣 on 5/2/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//
/*

#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here
*/
class Animal
{
public:
    Animal(string name)
    {
        m_name = name;
        move_way = "walk";
    }
    
    virtual ~Animal(){};
    
    virtual string name() const
    {
        return m_name;
    }
    
    virtual string moveAction() const
    {
        return move_way;
    }
    
    virtual void speak() const = 0;
    
    
private:
    string m_name;
    string move_way;

};

class Cat : public Animal
{
public:
    Cat(string name) : Animal(name)
    {}
    
    virtual ~Cat()
    {
        cout << "Destroying " << name() << " the cat" <<endl;
    }

    virtual void speak() const
    {
        cout << "Meow";
    }
    
private:

};

class Duck : public Animal
{
public:
    Duck(string name) : Animal(name)
    {}
    
    virtual string moveAction() const
    {
        return "swim";
    }

    virtual ~Duck()
    {
        cout << "Destroying " << name() << " the duck" <<endl;

    }
    
    virtual void speak() const
    {
        cout << "Quack";
    }

private:

};

class Pig : public Animal
{
public:
    Pig(string name, int lbs) : Animal(name), weight(lbs)
    {}
    
    virtual ~Pig()
    {
        cout << "Destroying " << name() << " the pig" <<endl;
    }
    
    virtual void speak() const
    {
        if (weight < 170)
            cout << "Oink";
        else
            cout << "Grunt";
    }

private:
    int weight;
    
};
/*
void animate(const Animal* a)
{
    a->speak();
    cout << "!  My name is " << a->name()
    << ".  Watch me " << a->moveAction() << "!\n";
}

int main()
{
    Animal* animals[4];
    animals[0] = new Cat("Fluffy");
    // Pigs have a name and a weight in pounds.  Pigs under 170
    // pounds oink; pigs weighing at least 170 pounds grunt.
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");
    
    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);
    
    // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
}


/*
 Here are the animals.
Meow!  My name is Fluffy.  Watch me walk!
Grunt!  My name is Napoleon.  Watch me walk!
Oink!  My name is Wilbur.  Watch me walk!
Quack!  My name is Daffy.  Watch me swim!
Cleaning up.
Destroying Fluffy the cat
Destroying Napoleon the pig
Destroying Wilbur the pig
Destroying Daffy the duck

above are the outputs 
 */






















