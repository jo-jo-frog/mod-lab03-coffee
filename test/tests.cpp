// Copyright 2026 Anisimov Kirill
#include <gtest/gtest.h>

#include "Automata.h"

TEST(AutomataTest, Constructor_InitialStateIsOffAndCashZero) {
  Automata machine;
  EXPECT_EQ(Automata::Status::OFF, machine.getStatus());
  EXPECT_DOUBLE_EQ(0.0, machine.getCash());
}

TEST(AutomataTest, On_SetsStateToWait) {
  Automata machine;
  machine.On();
  EXPECT_EQ(Automata::Status::WAIT, machine.getStatus());
}

TEST(AutomataTest, Off_SetsStateToOff) {
  Automata machine;
  machine.On();
  machine.Off();
  EXPECT_EQ(Automata::Status::OFF, machine.getStatus());
}

TEST(AutomataTest, Coin_IncreasesCashAndSetsAcceptState) {
  Automata machine;
  machine.On();
  machine.Coin(150.50);
  EXPECT_DOUBLE_EQ(150.50, machine.getCash());
  EXPECT_EQ(Automata::Status::ACCEPT, machine.getStatus());
}

TEST(AutomataTest, EtMenu_LoadsStaticMenu) {
  Automata machine;
  machine.On();
  machine.etMenu(1);
  EXPECT_TRUE(machine.isMenuLoaded());
  EXPECT_EQ(7, machine.getMenuSize());
  EXPECT_EQ("Эспрессо", machine.getMenuName(0));
  EXPECT_DOUBLE_EQ(120.50, machine.getPrice(0));
}

TEST(AutomataTest, Check_WithEnoughMoney_ReturnsTrueAndDeductsCash) {
  Automata machine;
  machine.On();
  machine.etMenu(1);
  machine.Coin(200.0);
  bool result = machine.Check(2);
  EXPECT_TRUE(result);
  EXPECT_DOUBLE_EQ(20.0, machine.getCash());
}

TEST(AutomataTest, Check_WithNotEnoughMoney_ReturnsFalseAndDoesNotDeduct) {
  Automata machine;
  machine.On();
  machine.etMenu(1);
  machine.Coin(100.0);
  bool result = machine.Check(2);
  EXPECT_FALSE(result);
  EXPECT_DOUBLE_EQ(100.0, machine.getCash());
}

TEST(AutomataTest, Choice_WithEnoughMoney_CooksAndDeductsCash) {
  Automata machine;
  machine.On();
  machine.etMenu(1);
  machine.Coin(200.0);
  machine.Choice(2);
  EXPECT_DOUBLE_EQ(20.0, machine.getCash());
  EXPECT_EQ(Automata::Status::WAIT, machine.getStatus());
}

TEST(AutomataTest, Choice_WithNotEnoughMoney_SetsStateCheck) {
  Automata machine;
  machine.On();
  machine.etMenu(1);
  machine.Coin(100.0);
  machine.Choice(2);
  EXPECT_DOUBLE_EQ(100.0, machine.getCash());
  EXPECT_EQ(Automata::Status::CHECK, machine.getStatus());
}

TEST(AutomataTest, Choice_WithoutMoney_ShowsErrorAndDoesNotChangeCash) {
  Automata machine;
  machine.On();
  machine.etMenu(1);
  machine.Choice(2);
  EXPECT_DOUBLE_EQ(0.0, machine.getCash());
  EXPECT_EQ(Automata::Status::WAIT, machine.getStatus());
}

TEST(AutomataTest, Cancel_ReturnsAllCashAndSetsWaitState) {
  Automata machine;
  machine.On();
  machine.etMenu(1);
  machine.Coin(300.0);
  machine.Choice(2);
  machine.Cancel();
  EXPECT_DOUBLE_EQ(0.0, machine.getCash());
  EXPECT_EQ(Automata::Status::WAIT, machine.getStatus());
}

TEST(AutomataTest, FullWorkflow_CompleteCycle) {
  Automata machine;

  machine.On();
  EXPECT_EQ(Automata::Status::WAIT, machine.getStatus());

  machine.etMenu(1);
  EXPECT_TRUE(machine.isMenuLoaded());

  machine.Coin(200.0);
  EXPECT_DOUBLE_EQ(200.0, machine.getCash());
  EXPECT_EQ(Automata::Status::ACCEPT, machine.getStatus());

  machine.Choice(2);
  EXPECT_DOUBLE_EQ(20.0, machine.getCash());
  EXPECT_EQ(Automata::Status::WAIT, machine.getStatus());

  machine.Cancel();
  EXPECT_DOUBLE_EQ(0.0, machine.getCash());

  machine.Off();
  EXPECT_EQ(Automata::Status::OFF, machine.getStatus());
}
