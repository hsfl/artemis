---
title: COSMOS Tutorial Part 3 - Building and Deploying
permalink: /pages/tutorials/cosmos/cosmos3.html
layout: series

tags: [software]
keywords: software
sidebar: home_sidebar
toc: false

series:
    language: "C++"
    prev: /pages/tutorials/cosmos/cosmos2.html
    next: /pages/tutorials/cosmos/cosmos4.html
---

## Build the Agent
To build the program, click the hammer icon at the bottom left of the screen. This will take a while on the first build since QtCreator needs to build the COSMOS Core source, but subsequent builds will be faster. If your program is bug-free, you'll see a green bar at the bottom right of QtCreator when the build is complete.

{% include image.html file="/resources/tutorials/cosmos/part3/build.png" width="100%" %}

> **_Note:_** if only you want to run the agent locally, you can just click on the green triangle, and skip the next section.

## Deploy the Agent on the BeagleBone

> **_Note:_** you can skip this step if you only want to test your agent locally.

> **_Tip:_** if you haven't used the Cloud9 IDE with the BeagleBone before, you should check out the
> [Getting Started tutorial series]({{site.folder_tutorials_setup}}/setup1.html)

Next, you'll need to deploy your agent to the BeagleBone, meaning that you will be moving the agent executables from your local computer onto the BeagleBone.

## Copy the Executable

You can copy the build folder to the BeagleBone by running the following terminal command:

```bash
rsync -auv ~/cosmos/source/projects/my_project/build-beaglebone debian@beaglebone.local:/home/debian
```

> **_Note:_** The `~/cosmos/source/projects/my_project/build-beaglebone` folder is what you are copying to the BeagleBone and the `/home/debian` folder is where you are putting it on the BeagleBone. 
> When copying any executables, you should follow this format of 
> ```bash
> rsync -auv FOLDER_COPYING debian@beaglebone.local:FOLDER_RECEIVING
> ```

Enter the password (default is `temppwd`), and wait a minute while the files copy over. From Cloud9 on the BeagleBone you should see the build folder appear in the home directory (`/home/debian`):

{% include image.html file="/resources/tutorials/cosmos/part3/cloud9.png" %}

### Run the Agent


To run the agent, you can enter the following command in a Cloud9 terminal:

```bash
~/build-beaglebone/my_agent
```

> **_Note:_** if you get an error when trying to run the program, run the following command to give the file "execute" permission and enter the password (default is `temppwd`):
> ```bash
> sudo chmod +x ~/build-beaglebone/my_agent
> ```

You should now see the output from your agent!


{% include image.html file="/resources/tutorials/cosmos/part3/run_agent.png" %}


## Try Calling a Request

Now that the agent is up and running, you can try calling the `say_hi` request we added in the previous section.
To call an agent request from a terminal, we use the following syntax:

```
$ agent <node name> <agent name> <request name> [request arguments...]
```

In this case the node name is `cubesat` by default, the agent name is `my_agent`, the request name is `say_hi`, and
we don't need to supply it with any arguments.


Open up another terminal and try it out:

```bash
$ agent cubesat my_agent say_hi
```

{% include image.html file="/resources/tutorials/cosmos/part3/call_request.png" width="100%" %}

> **_Note:_** the screenshot above is for running agents on the BeagleBone. If you're testing locally, then
> you will be using Ubuntu's terminal.

## Stop the Agent

Once you're done testing out your agents, you should terminate them by pressing
<kbd>Control</kbd> + <kbd>C</kbd> in their terminal window.





