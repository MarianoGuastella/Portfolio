def tickets(line):
    """Function that returns if it's possible to give change receiving 25, 50 and 100 bills.
    Note that initial change is set to 0.

    Parameters:
    line(List): A list with possible values being the bills mentioned previously.

    Returns:
    is_possible(str): If it's possible to give everyone their respective change will be "YES",
    otherwise "NO".
    """
	cash = [0, 0] #25 and 50 bill
	is_possible = "YES"

	if not line:
		return is_possible

	for payment in line:
		if payment == 50:
            if cash[0] >= 1:
                cash[0] -= 1
            else:
                is_possible = "NO"
                break

        elif payment == 100:
            if cash[1] >= 1 and cash[0] >= 1:
                cash[1] -= 1
                cash[0] -= 1
            elif cash[0] >= 3:
                cash[0] -= 3
            else:
                is_possible = "NO"
                break

        else:
            cash[0] += 1

    return is_possible
