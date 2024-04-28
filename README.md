# Cbank

Cbank is a simple command-line banking application written in C. It allows users to sign in or sign up, deposit and withdraw money, request loans, and delete their accounts. The application stores user credentials and account balances in text files locally.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Introduction
Program has missing features like loan updates which can make it unsusable.
Tip: Compiled file works only for linux.

Cbank is designed to provide a basic banking experience in a command-line environment. It offers essential functionalities such as account management, transactions, and loan requests.

## Features

- **Sign-in and Sign-up**: Users can sign in with existing credentials or create a new account.
- **Deposit and Withdraw**: Users can deposit money into their accounts or withdraw funds.
- **Loan Requests**: Users can request loans with a fixed interest rate.
- **Account Deletion**: Users can delete their accounts permanently.

## Usage

To use Cbank, follow these steps:

1. Compile the source code using a C compiler.
2. Run the compiled executable.
3. Choose from the available options to sign in, sign up, or perform transactions.

## Installation

To install Cbank, you need a C compiler such as GCC:

```bash
gcc bank.c -o cbank

