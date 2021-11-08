# ------------------------------------------------------------------------------
# Plant.py - provides declaration and implementation for the plant-class
# and functions working with it.
# ------------------------------------------------------------------------------
import random
import string
from typing import TextIO


class Plant(object):

    def countVowelProportion(self) -> None:
        """
        A function which counts vowel count proportion for a specific plant.

        :return: -
        """
        self.vowel_count_proportion_: float = 0.0
        if self.name_length_ == 0:
            return
        for ch in self.name_:
            self.vowel_count_proportion_ += 1 if isAVowel(ch) else 0
        self.vowel_count_proportion_ /= self.name_length_

    def __init__(self, is_random: bool, params: list) -> None:
        """
        Special constructor, which has different ways of creating a
        "plant"-object depending on what type of input was selected.

        :param is_random: Logical parameter, specifying a method of extracting input data -
        random generation or file-input.

        :param params: A list of params passed in case of file-input.
        """
        if is_random:
            self.name_ = randomName(random.randint(1, 20))
        else:
            if params.__len__() < 2:
                self = 0
                return
            if params[1].__len__() > 20:
                params[1] = params[1][:20]
            self.name_ = params[1]
        self.name_length_ = len(self.name_)
        self.vowel_count_proportion_ = 0
        self.countVowelProportion()

    def toString(self) -> str:
        """
        A function to get string-type presentation of plant-data.

        :return: A string, containing information about a plant.
        """
        return f"{self.name_}: VowelInNameProportion = {self.vowel_count_proportion_: .2f}"


def isAVowel(ch: str) -> bool:
    """
    Additional function, used to determine if the input-character belongs to a group of vowels.

    :param ch: Character to be analyzed.

    :return: True if the character is a vowel and False otherwise.
    """
    vowel_switch = {
        'a': True,
        'e': True,
        'i': True,
        'o': True,
        'y': True,
        'u': True
    }
    return vowel_switch.get(ch, False)


def randomName(length: int) -> str:
    """
    Additional function, which constructs a pseudo-random (lowercase) name of a specific length.

    :param length: Name length.

    :return: A string-object for a constructed pseudo-random name.
    """
    result: str = ""
    for index in range(length):
        result += random.choice(string.ascii_lowercase)
    return result
