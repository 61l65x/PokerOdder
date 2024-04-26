# PokerOdder

#### For now only builds a little simulations table with the library

## Overview
The Poker Odds Calculator is a tool designed to calculate the odds and probabilities in various poker games using the robust `PokerHandEvaluator` library. This application is built in C++ and utilizes advanced algorithms to deliver quick and accurate results.

## Features
- Calculate odds for different poker hands.
- Utilize the `PokerHandEvaluator` library for efficient hand evaluation.
- Simple command-line interface for easy interaction.

## Getting Started

### Prerequisites
Ensure you have `git` and a C++ compiler supporting at least C++11 standard. This project is tested on Linux and macOS.

### Cloning the Repository
This project includes a submodule for the `PokerHandEvaluator` library. To clone the project along with its submodule, use the following command:

```bash
git clone --recurse-submodules https://github.com/Jallunator/PokerOdder.git

#If you have already cloned the repository without the submodules, you can fetch the submodules using:
git submodule update --init --recursive

# Building the project
cd PokerOddsCalculator
make

```
