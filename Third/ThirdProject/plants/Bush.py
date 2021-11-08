# ------------------------------------------------------------------------------
# Bush.py - provides declaration and implementation for the bush-class
# and functions working with it.
# ------------------------------------------------------------------------------
import random
from plants.Plant import Plant
from enum import IntEnum


class Bush(Plant):
    class BlossomMonth(IntEnum):
        JANUARY = 1
        FEBRUARY = 2
        MARCH = 3
        APRIL = 4
        MAY = 5
        JUNE = 6
        JULY = 7
        AUGUST = 8
        SEPTEMBER = 9
        OCTOBER = 10
        NOVEMBER = 11
        DECEMBER = 12

    def __init__(self, is_random: bool, params: list) -> None:
        """
        Special constructor, which has different ways of creating a
        "bush"-object depending on what type of input was selected.

        :param is_random: Logical parameter, specifying a method of extracting input data -
        random generation or file-input.

        :param params: A list of params passed in case of file-input.
        """
        super().__init__(is_random, params)
        if is_random:
            self.blossom_month_ = Bush.BlossomMonth(random.randint(1, 12))
        else:
            if params.__len__() < 3:
                self = 0
                return
            self.blossom_month_ = abs(int(params[2]))
            self.blossom_month_ = Bush.BlossomMonth(self.blossom_month_ % 12 + 1
                                                    if ((self.blossom_month_ == 0) or (self.blossom_month_ > 12))
                                                    else self.blossom_month_)

    def getMonth(self) -> str:
        """
        A function to get string-type presentation of a month of blossom for a specific bush.

        :return: A string, containing information about a month when a bush blossoms in.
        """
        month_switch = {
            Bush.BlossomMonth.JANUARY: "January",
            Bush.BlossomMonth.FEBRUARY: "February",
            Bush.BlossomMonth.MARCH: "March",
            Bush.BlossomMonth.APRIL: "April",
            Bush.BlossomMonth.MAY: "May",
            Bush.BlossomMonth.JUNE: "June",
            Bush.BlossomMonth.JULY: "July",
            Bush.BlossomMonth.AUGUST: "August",
            Bush.BlossomMonth.SEPTEMBER: "September",
            Bush.BlossomMonth.OCTOBER: "October",
            Bush.BlossomMonth.NOVEMBER: "November",
            Bush.BlossomMonth.DECEMBER: "December"
        }
        return month_switch.get(self.blossom_month_, "undefined")

    def toString(self) -> str:
        """
        A function to get string-type presentation of bush-data.

        :return: A string, containing information about a bush.
        """
        return f"Bush {super().toString()}: {self.getMonth()}"
