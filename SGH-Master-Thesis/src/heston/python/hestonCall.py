from numpy.ma import exp
from scipy.constants import pi

__author__ = 'konrad'


def hestoncalibrate():
    print 'dupa'


def preset_value(time):
    pass


def pdf(volatility):
    pass


def heston_call_option_price(asset_price, volatility, strike, time):
    return asset_price * pdf(volatility) - strike * preset_value(time) * pdf(volatility)


print heston_call_option_price()