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
        if (size == CupSize::Little)
        {
            m_ingdridient->AddWater(50, 60);
            m_ingdridient->AddCoffee(50);
        }
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


