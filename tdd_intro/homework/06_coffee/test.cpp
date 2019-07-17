/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

/*
Our machine should be able to produce the coffee accordingly to the next receipts:

Americano: water & coffee 1:2 or 1:3. Water temp 60C
Cappuccino: milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
Latte: milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
Marochino: chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty
We have 2 possible sizes of the cup:

Little 100 gram
Big 140 gram
Implement worked coffee machine using ISourceOfIngredients to control the process of coffee production.
*/


enum CupSize
{
    Big,
    Little
};

class CoffeeMachine
{
public:
    CoffeeMachine(std::unique_ptr<ISourceOfIngredients> ingridient)
        : m_ingdridient(std::move(ingridient))
    {
    }

    void MakeAmericano(CupSize size)
    {
        int size_of_ingridient = (size == CupSize::Little) ? 50: 70;

        m_ingdridient->AddWater(size_of_ingridient, 60);
        m_ingdridient->AddCoffee(size_of_ingridient);
    }

    void MakeCappuccino(CupSize size)
    {
        int size_of_ingridient = (size == CupSize::Little) ? 33: 46;

        m_ingdridient->AddMilk(size_of_ingridient);
        m_ingdridient->AddCoffee(size_of_ingridient);
        m_ingdridient->AddMilkFoam(size_of_ingridient);
    }

    void MakeLatte(CupSize size)
    {
        int size_of_coffee = 0;
        int size_of_other = 0;

        if (size == CupSize::Little)
        {
            size_of_coffee = 50;
            size_of_other = 25;
        }
        else
        {
            size_of_coffee = 70;
            size_of_other = 35;
        }

        m_ingdridient->AddMilk(size_of_other);
        m_ingdridient->AddCoffee(size_of_coffee);
        m_ingdridient->AddMilkFoam(size_of_other);
    }
    void MakeMarochino(CupSize size)
    {

    }



private:
    std::unique_ptr<ISourceOfIngredients> m_ingdridient;
};


class MockSourceOfIngridient: public ISourceOfIngredients
{
public:
    MOCK_METHOD1(SetCupSize, void (int gram));
    MOCK_METHOD2(AddWater, void(int gram, int temperature));
    MOCK_METHOD1(AddSugar, void(int gram));
    MOCK_METHOD1(AddCoffee, void(int gram));
    MOCK_METHOD1(AddMilk, void(int gram));
    MOCK_METHOD1(AddMilkFoam, void(int gram));
    MOCK_METHOD1(AddChocolate, void(int gram));
    MOCK_METHOD1(AddCream, void(int gram));
};

TEST(CoffeeMachine, make_little_americano)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddWater(50, 60)).Times(1);
    EXPECT_CALL(*ingridient, AddCoffee(50)).Times(1);

    CoffeeMachine machine(std::move(ingridient));

    machine.MakeAmericano(CupSize::Little);
}


TEST(CoffeeMachine, make_big_americano)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddWater(70, 60)).Times(1);
    EXPECT_CALL(*ingridient, AddCoffee(70)).Times(1);

    CoffeeMachine machine(std::move(ingridient));

    machine.MakeAmericano(CupSize::Big);
}

TEST(CoffeeMachine, make_little_capuchino)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddMilk(33));
    EXPECT_CALL(*ingridient, AddCoffee(33));
    EXPECT_CALL(*ingridient, AddMilkFoam(33));

    CoffeeMachine machine(std::move(ingridient));
    machine.MakeCappuccino(CupSize::Little);
}

TEST(CoffeeMachine, make_big_capuchino)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddMilk(46));
    EXPECT_CALL(*ingridient, AddCoffee(46));
    EXPECT_CALL(*ingridient, AddMilkFoam(46));

    CoffeeMachine machine(std::move(ingridient));
    machine.MakeCappuccino(CupSize::Big);
}

TEST(CoffeeMachine, make_little_late)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddMilk(25));
    EXPECT_CALL(*ingridient, AddCoffee(50));
    EXPECT_CALL(*ingridient, AddMilkFoam(25));

    CoffeeMachine machine(std::move(ingridient));
    machine.MakeLatte(CupSize::Little);
}

TEST(CoffeeMachine, make_big_late)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddMilk(35));
    EXPECT_CALL(*ingridient, AddCoffee(70));
    EXPECT_CALL(*ingridient, AddMilkFoam(35));

    CoffeeMachine machine(std::move(ingridient));
    machine.MakeLatte(CupSize::Big);
}

TEST(CoffeeMachine, make_little_marochino)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddChocolate(25));
    EXPECT_CALL(*ingridient, AddCoffee(25));
    EXPECT_CALL(*ingridient, AddMilkFoam(25));

    CoffeeMachine machine(std::move(ingridient));
    machine.MakeMarochino(CupSize::Little);
}

TEST(CoffeeMachine, make_big_marochino)
{
    std::unique_ptr<MockSourceOfIngridient> ingridient(new MockSourceOfIngridient());

    EXPECT_CALL(*ingridient, AddChocolate(35));
    EXPECT_CALL(*ingridient, AddCoffee(35));
    EXPECT_CALL(*ingridient, AddMilkFoam(35));

    CoffeeMachine machine(std::move(ingridient));
    machine.MakeMarochino(CupSize::Big);
}

