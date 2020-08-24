# SilentDragonLite 
[![GitHub license](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://github.com/MyHush/SilentDragonLite/blob/master/LICENSE)
[![GitHub version](https://badge.fury.io/gh/MyHush%2FSilentDragonLite.svg)](https://badge.fury.io/gh/MyHush%2FSilentDragonLite)
[![Github All Releases](https://img.shields.io/github/downloads/MyHush/SilentDragonLite/total.svg)](https://img.shields.io/github/downloads/MyHush/SilentDragonLite/total.svg)

<p align="left">
    <a href="https://twitter.com/MyHushTeam">
        <img src="https://img.shields.io/twitter/url?style=social&url=https%3A%2F%2Ftwitter.com%2Fmyhushteam"
            alt="MyHushTeam's Twitter"></a>
    <a href="https://twitter.com/intent/follow?screen_name=MyHushTeam">
        <img src="https://img.shields.io/twitter/follow/MyHushTeam?style=social&logo=twitter"
            alt="follow on Twitter"></a>
    <a href="https://fosstodon.org/@myhushteam">
        <img src="https://img.shields.io/badge/Mastodon-MyHushTeam-blue"
            alt="follow on Mastodon"></a>
    <a href="https://www.reddit.com/r/Myhush/">
        <img src="https://img.shields.io/reddit/subreddit-subscribers/Myhush?style=social"
            alt="MyHushTeam's Reddit"></a>
</p>

SilentDragonLite is a lightwallet for HUSH ($HUSH) which runs on Linux and Windows. This does not require you to download the full blockchain. This is experimental software under active development!

<img src="https://raw.githubusercontent.com/MyHush/SilentDragonLite/master/hushchat-screenshot.png">

## PRIVACY NOTICE

SilentDragonLite contacts a few different external websites to get various bits of data.

	* coingecko.com for price data API 
	* explorer.myhush.org for explorer links 
	* dexstats.info for address utilities 
	* hush-lightwallet.de to get Data

This means your IP address is known to these servers. Enable Tor setting in SilentDragonLite to prevent this, or better yet, use TAILS: https://tails.boum.org/

## Installation

Go to the [releases page](https://github.com/MyHush/SilentDragonLite/releases) and grab the latest installers or binary. For any Arch Linux users, we also have packages on [AUR](https://aur.archlinux.org/) which can be installed with **[yay -S silentdragonlite](https://aur.archlinux.org/packages/silentdragonlite/)** or with **[yay -S silentdragonlite-appimage](https://aur.archlinux.org/packages/silentdragonlite-appimage/)** for the AppImage package.

## Install Torsocks (or any other Socks service for TOR) on Ubuntu 18.04
```
sudo apt update
sudo apt install torsocks
```
## Connection to our TOR onion service Server
```
* Open SDL  Edit->Settings->LightwalletServer->6onaaujm4ozaokzu.onion:80
* Open the folder of SDL in a Terminal -> Enter: TORSOCKS_LOG_LEVEL=1 torsocks -i ./SilentDragonLite
```
## Note Management
SilentDragonLite does automatic note and utxo management, which means it doesn't allow you to manually select which address to send outgoing transactions from. It follows these principles:
* Defaults to sending shielded transactions, even if you're sending to a transparent address
* Sapling funds need at least 2 confirmations before they can be spent
* Can select funds from multiple shielded addresses in the same transaction
* Will automatically shield your transparent funds at the first opportunity
* When sending an outgoing transaction to a shielded address, SilentDragonLite can decide to use the transaction to additionally shield your transparent funds (i.e., send your transparent funds to your own shielded address in the same transaction)

## Compiling from source
* SilentDragonLite is written in C++ 14, and can be compiled with g++/clang++/visual c++. 
* It also depends on Qt5, which you can get from [here](https://www.qt.io/download). 
* You'll need Rust v1.41 +

### Building on Linux

```
git clone https://github.com/MyHush/SilentDragonLite.git
cd SilentDragonLite
./build.sh
./SilentDragonLite

```

## Support

For support or other questions, join us on [Discord](https://myhush.org/discord), or tweet at [@MyHushTeam](https://twitter.com/MyHushTeam), or toot at our [Mastodon](https://fosstodon.org/@myhushteam), or join [Telegram](http://myhush.org/telegram) or [file an issue](https://github.com/MyHush/SilentDragonLite/issues).

