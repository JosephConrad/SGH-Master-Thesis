from numpy.ma import exp
from scipy.constants import pi

__author__ = 'konrad'


def hestoncalibrate():
    print 'dupa'


def preset_value(time):
    pass


def pdf(volatility):
    pass


def fj(c, d, vt, phi, x):
    return exp(c + d * vt + 1j * phi * x)


def heston_call_option_price(asset_price, volatility, strike, time):
    return asset_price * pdf(volatility) - strike * preset_value(time) * pdf(volatility)


# print heston_call_option_price()

print fj(-1, 1, 1, 1, 1)