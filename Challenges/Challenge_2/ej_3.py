def move_claw(clawPos, dest, commands):
    """Moves the claw from a starting position to destination and adds the corresponding
    commands.

    Parameters:
    clawPos(int): Starting positon
    dest(int): Destination index
    commands(list): List of commands

    return:
    dest(int): Final position of the claw
    """
    if dest < clawPos:
        commands.extend(["LEFT"] * (clawPos - dest))
    if dest > clawPos:
        commands.extend(["RIGHT"] * (dest - clawPos))
    return dest

def place_box(clawPos, dest, boxes, commands):
    """Places a box from a starting position to a destination position and adds the 
    corresponding commands.
    
    Parameters:
    clawPos(int): Starting positon
    dest(int): Destination index
    boxes(list): List of boxes
    commands(list): List of commands
    
    return:
    clawPos(int): Final position of the claw
    """
    clawPos = move_claw(clawPos, dest, commands)
    boxes[dest] += 1
    commands.append("PLACE")
    return clawPos

def pick_up_box(clawPos, dest, boxes, commands):
    """Moves a destination, picks up a box and adds the corresponding commands.

    Parameters:
    clawPos(int): Starting positon
    dest(int): Destination index
    boxes(list): List of boxes
    commands(list): List of commands
    
    return:
    clawPos(int): Final position of the claw
    """
    clawPos = move_claw(clawPos, dest, commands)
    commands.append("PICK")
    boxes[dest] -= 1
    return clawPos

def min_stacks_larger_than_average(boxes, average_boxes):
    """Returns whether the boxes are properly distributed with a maximum variation of one box
    between stacks"""
    return max(boxes) > average_boxes + 1 or min(boxes) < average_boxes

def boxes_are_in_descending_order(i, j, boxes):
    """Returns if indexes go over, that means boxes are in descending order, and if all stacks 
    have the same quantity of boxes, so it doesn't move any box in that case"""
    return not((i < j) and not(all(element == boxes[0] for element in boxes)))

def r_max_index(boxes):
    """Returns the index of the maximum element from right to left of boxes"""
    return len(boxes) - boxes[::-1].index(max(boxes)) - 1

def solve(clawPos, boxes, boxInClaw):
    """Rearranges the stacks in order to have an equal number of boxes on each stack.
    If this is not possible, any excess box is stacked from left to right.
    First it places the box carried by the arm.
    Then properly distributes the boxes with a maximum variation of one box between stacks.
    Finally orders the boxes in a descendant order from left to right and returns the 
    commands list.
    
    Parameters:
    clawPos(int): Current position of the claw
    boxes(list): List of the stacks with boxes
    boxInClaw(int): 1 if the arm is carrying a box, 0 otherwise

    return:
    commands(list): List of commands in order to archieve the desired order
    """
    average_boxes = sum(boxes) // len(boxes)
    commands = []

    if boxInClaw == 1:
        if min(boxes) >= 5:
            commands.append("WARNING")
            return commands
        dest = boxes.index(min(boxes))
        clawPos = place_box(clawPos, dest, boxes, commands)
        boxInClaw = 0

    while min_stacks_larger_than_average(boxes, average_boxes):
        dest = boxes.index(max(boxes))
        clawPos = pick_up_box(clawPos, dest, boxes, commands)
        dest = boxes.index(min(boxes))
        clawPos = place_box(clawPos, dest, boxes, commands)

    i = boxes.index(min(boxes))
    j = r_max_index(boxes)
    while not boxes_are_in_descending_order(i, j, boxes):
        clawPos = pick_up_box(clawPos, j, boxes, commands)
        clawPos = place_box(clawPos, i, boxes, commands)
        i = boxes.index(min(boxes))
        j = r_max_index(boxes)

    return commands
