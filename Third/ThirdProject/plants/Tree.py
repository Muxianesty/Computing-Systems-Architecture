# ------------------------------------------------------------------------------
# Tree.py - provides declaration and implementation for the tree-class
# and functions working with it.
# ------------------------------------------------------------------------------
from plants.Plant import *


class Tree(Plant):

    def __init__(self, is_random: bool, params: list) -> None:
        """
        Special constructor, which has different ways of creating a
        "tree"-object depending on what type of input was selected.

        :param is_random: Logical parameter, specifying a method of extracting input data -
        random generation or file-input.

        :param params: A list of params passed in case of file-input.
        """
        if not is_random and params.__len__() < 3:
            self = 0
            return
        super().__init__(is_random, params)
        self.age_ = random.randint(0, 500) if is_random else abs(int(params[2])) % 501

    def toString(self) -> str:
        """
        A function to get string-type presentation of tree-data.

        :return: A string, containing information about a tree.
        """
        return f"Tree {super().toString()}: {self.age_} years old"
