#python version tic tac toe game
import random


def human_step():
    posit = input("Your turn. Enter a number: ")
    while posit not in "123456789":
        posit = input("Please enter a valid cell number: ")
    posit = int(posit) - 1
    while group[posit] != " ":
        posit = input("Please enter a valid cell number: ")
        posit = int(posit) - 1
    return posit


def pc_step():
    if step == 0:
        pro_step = [0, 2, 4, 6, 8]
        position = random.randint(0, 4)
        return pro_step[position]
    elif step == 2:
        if group[4] == "X":
            cor_step = [0, 2, 6, 8]
            for i in range(4):
                if group[cor_step[i]] == "O":
                    posit = 0
                    if cor_step[i] == 0:
                        posit = 8
                    elif cor_step[i] == 8:
                        posit = 0
                    elif cor_step[i] == 2:
                        posit = 6
                    elif cor_step[i] == 6:
                        posit = 2
                    return posit
            nearby = [0, 0]
            if group[1] == "O":
                nearby[0] = 0
                nearby[1] = 2
            elif group[3] == "O":
                nearby[0] = 0
                nearby[1] = 6
            elif group[5] == "0":
                nearby[0] = 2
                nearby[1] = 8
            elif group[7] == "0":
                nearby[0] = 6
                nearby[1] = 8
            posit = nearby[random.randint(0, 1)]
            return posit
        else:
            if group[4] == " ":
                return 4
            posit = 0
            if group[0] == "X":
                posit = 8
            elif group[8] == "X":
                posit = 0
            elif group[2] == "X":
                posit = 6
            elif group[6] == "X":
                posit = 2
            return posit
    else:
        first_arr = check_three("X", group)
        if len(first_arr) != 0:
            posit = first_arr[0]
            return posit
        second_arr = check_three("O", group)
        if len(second_arr) != 0:
            posit = second_arr[0]
            return posit
        third_posit = 0
        third_max = -1
        for temp in range(9):
            if group[temp] == " ":
                if third_max == -1:
                    third_posit = temp
                    third_max = 0
                temp_group = group.copy()
                temp_arr = check_three("X", temp_group)
                if len(temp_arr) > third_max:
                    third_max = len(temp_arr)
                    third_posit = temp
        return third_posit


def whose_turn():
    if step % 2 == 0:
        return "cp"
    if step % 2 == 1:
        return "human"


def check_three(kind, gp):
    situation = []
    all_possible = [[0, 1, 2], [3, 4, 5], [6, 7, 8], [0, 3, 6], [1, 4, 7], [2, 5, 8], [0, 4, 8], [2, 4, 6]]
    for i in range(8):
        x = all_possible[i][0]
        y = all_possible[i][1]
        z = all_possible[i][2]
        if (gp[x] == kind and gp[y] == kind and gp[z] == " ") or (gp[x] == kind and gp[y] == " " and gp[z] == kind) or (gp[x] == " " and gp[y] == kind and gp[z] == kind):
            if gp[x] == " ":
                situation.append(x)
            elif gp[y] == " ":
                situation.append(y)
            elif gp[z] == " ":
                situation.append(z)
    return situation


def result(state):
    if state == "X":
        print("Aha, you lose!")
    elif state == "O":
        print("Wow, you win!")
    elif state == " ":
        print("Tie! Try again.")


def game_over():
    if group[0] == group[1] and group[1] == group[2] and group[0] != " ":
        result(group[0])
        return True
    elif group[3] == group[4] and group[4] == group[5] and group[3] != " ":
        result(group[3])
        return True
    elif group[6] == group[7] and group[7] == group[8] and group[6] != " ":
        result(group[6])
        return True
    elif group[0] == group[3] and group[3] == group[6] and group[0] != " ":
        result(group[0])
        return True
    elif group[1] == group[4] and group[4] == group[7] and group[1] != " ":
        result(group[1])
        return True
    elif group[2] == group[5] and group[5] == group[8] and group[2] != " ":
        result(group[2])
        return True
    elif group[0] == group[4] and group[4] == group[8] and group[0] != " ":
        result(group[0])
        return True
    elif group[2] == group[4] and group[4] == group[6] and group[2] != " ":
        result(group[2])
        return True
    else:
        is_tie = True
        for i in range(9):
            if group[i] == " ":
                is_tie = False
        if is_tie:
            result(" ")
            return True
        else:
            return False


def print_board(gp):
    print("\t\t| " + str(gp[0]) + " | " + str(gp[1]) + " | " + str(gp[2]) + " |")
    print("\t\t|-----------|")
    print("\t\t| " + str(gp[3]) + " | " + str(gp[4]) + " | " + str(gp[5]) + " |")
    print("\t\t|-----------|")
    print("\t\t| " + str(gp[6]) + " | " + str(gp[7]) + " | " + str(gp[8]) + " |")


group = [" ", " ", " ", " ", " ", " ", " ", " ", " "]
step = 0
print("Choose a cell numbered from 1 to 9 as below and play.")
print("\t\t| 1 | 2 | 3 |")
print("\t\t|-----------|")
print("\t\t| 4 | 5 | 6 |")
print("\t\t|-----------|")
print("\t\t| 7 | 8 | 9 |")

while not game_over():
    turn = whose_turn()
    if turn == "human":
        group[human_step()] = "O"
        print("Human has done. Computer's turn.")
    if turn == "cp":
        group[pc_step()] = "X"
        print("Computer has done.")
    print_board(group)
    step += 1


