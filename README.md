<div align="center">
  <img src="https://github.com/FrederoxDev/Amethyst/assets/69014593/08e43b26-05e2-4646-968b-0d3ab6699d78" alt="Image" width="300" height="300" />
  <h1>Project Amethyst
    <br />
    <a href="https://discord.gg/Cxrj9UXnDB"><img alt="Discord" src="https://img.shields.io/discord/1184966397864980601?color=5865f2&label=Discord&style=flat" /></a>
    <img alt="GitHub Downloads (all assets, all releases)" src="https://img.shields.io/github/downloads/FrederoxDev/Amethyst/total">
  </h1>
</div>

Project Amethyst is an open source-project for building client-side mods for Minecraft Bedrock `1.20.71.1`, client-side mods are able to stretch past the limitations of addons and have full control over the game such as using Minecraft's input system, creating your own user interfaces, changing vanilla functionality, and more. Please consider starring ⭐ the repository, doing this takes a significant amount of work.

<br />
<h2 align="center">Mods built with Amethyst</h2>

### - [Better Inventory](https://github.com/FrederoxDev/Better-Inventory)

| ![image](https://github.com/FrederoxDev/Better-Inventory/assets/69014593/a6f26fd7-f934-4a9a-95ba-5f03eb950509) | ![image](https://github.com/FrederoxDev/Better-Inventory/assets/69014593/97290890-1a12-4c61-a9ac-407bf78289d6) |
|----------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------|

Better Inventory is an inventory improvement mod for Minecraft Bedrock edition, version `1.20.71.1`. It adds in a shulker box preview, as well as the ability to see extra information about other items, like its identifier, namespace, durability and aux id.

<br />

### - [VidereLonge](https://github.com/AmethystAPI/VidereLonge)

| Before Zoom                                                                                            | After Zoom                                                                                             |
|--------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------|
| ![image](https://github.com/FrederoxDev/Amethyst/assets/69014593/c08ba235-3ac0-427a-b66b-3e5c69a56996) | ![image](https://github.com/FrederoxDev/Amethyst/assets/69014593/43c797db-4a67-470a-afae-5719bfbca1ce) |

A small mod which adds in an "Optifine" like zoom into the game.

<br />

### - [Sky's the limit](https://github.com/Adrian8115/Skys-the-Limit)

| ![image](https://github.com/Adrian8115/Skys-the-Limit/blob/8c60833de0e20860e36b4e2212be04bc5bb813cf/assets/img1.png) | ![image](https://github.com/Adrian8115/Skys-the-Limit/blob/8c60833de0e20860e36b4e2212be04bc5bb813cf/assets/img2.png) |
|----------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------|

A simple Minecraft Bedrock mod that increases the maximum build limit in all dimensions to 2048 blocks.

### Using the API for other projects

To link AmethystAPI with another mod, we use an environment variable `%amethyst_src%` to point to the cloned repository. Here is a quick list of commands to clone Amethyst into the Documents folder and setup the environment variable automatically.
```ps
powershell
$destination = Join-Path $env:USERPROFILE "Documents/Amethyst"
git clone https://github.com/FrederoxDev/Amethyst.git $destination
[System.Environment]::SetEnvironmentVariable("amethyst_src", $destination, "User")
```
