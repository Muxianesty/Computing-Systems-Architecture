# ------------------------------------------------------------------------------
# Flower.py - provides declaration and implementation for the flower-class
# and functions working with it.
# ------------------------------------------------------------------------------
import random
from plants.Plant import Plant
from enum import IntEnum


class Flower(Plant):

    class FlowerType(IntEnum):
        DOMESTIC = 1
        GARDEN = 2
        WILD = 3

    def __init__(self, is_random: bool, params: list) -> None:
        """
        Special constructor, which has different ways of creating a
        "flower"-object depending on what type of input was selected.

        :param is_random: Logical parameter, specifying a method of extracting input data -
        random generation or file-input.

        :param params: A list of params passed in case of file-input.
        """
        super().__init__(is_random, params)
        if is_random:
            self.flower_type_ = Flower.FlowerType(random.randint(1, 3))
        else:
            if params.__len__() < 3:
                self = 0
                return
            self.flower_type_ = abs(int(params[2]))
            self.flower_type_ = Flower.FlowerType(self.flower_type_ % 3 + 1
                                                  if ((self.flower_type_ == 0) or (self.flower_type_ > 3))
                                                  else self.flower_type_)

    def getType(self) -> str:
        """
        A function to get string-type presentation of a type for a specific flower.

        :return: A string, containing information about a flower-type.
        """
        type_switch = {
            Flower.FlowerType.DOMESTIC: "Domestic",
            Flower.FlowerType.GARDEN: "Garden",
            Flower.FlowerType.WILD: "Wild"
        }
        return type_switch.get(self.flower_type_, "undefined")

    def toString(self) -> str:
        """
        A function to get string-type presentation of flower-data.

        :return: A string, containing information about a flower.
        """
        return f"Flower {super().toString()}: {self.getType()}"
