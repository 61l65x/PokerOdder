# PokerOdder

#### For now only builds a little simulations table with the library

## Overview
The Poker Odds Calculator is a tool designed to calculate the odds and probabilities in various poker games using the robust `PokerHandEvaluator` library. This application is built in C++ and utilizes advanced algorithms, including Monte Carlo simulations, to deliver quick and accurate results. The program evaluates the strength of hands across different scenarios, providing a comprehensive analysis for the user.

## Features
- Calculate odds for different poker hands.
- Utilize the `PokerHandEvaluator` library for efficient hand evaluation.
- Use Monte Carlo simulations to assess hand strength in various scenarios.
- Simple command-line interface for easy interaction.

## Getting Started

### Prerequisites
Ensure you have `git` and a C++ compiler supporting at least C++11 standard. This project is tested on Linux and macOS.

### Cloning the Repository
This project includes submodules for the `PokerHandEvaluator` and `imgui` libraries. To clone the project along with its submodules, use the following command:

```bash
git clone --recurse-submodules https://github.com/Jallunator/PokerOdder.git

# If you have already cloned the repository without the submodules, you can fetch the submodules using:
git submodule update --init --recursive


# Building the project
cd PokerOddsCalculator
make

```
