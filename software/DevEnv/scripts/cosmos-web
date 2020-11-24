#!/bin/bash

usage() {
    echo "Usage: cosmos_web [-s]"
    echo "    > -s       Start npm and agent_mongo in separate terminals"
}

# Check parameters
if [[ $1 = "-h" ]]; then
    usage
    exit
fi

if [[ "$#" -gt 1 || (! -z "$1" && $1 != "-s") ]]; then
    usage
    exit
fi


# Load configuration values
source config


intexit() {
    # Stop MongoDB
    sudo systemctl stop mongod

    # Kill all subprocesses
    kill -HUP -$$
}

hupexit() {
    echo
    echo "Interrupted"
    exit
}




# ======================= Start MongoDB =======================
echo "Starting MongoDB..."
sudo systemctl start mongod

# Check if MongoDB failed to start
if ( ! systemctl --quiet is-active mongod ); then
    echo "Failed to start MongoDB"
    exit
fi



# Set traps so the script exits properly
trap hupexit HUP
trap intexit INT



# ======================= Start Agent Mongo =======================
echo "Starting agent_mongo..."

if [[ $1 != "-s" ]]; then
    # Start in the same terminal
    $AGENT_MONGO_FOLDER/agent_mongo &
else
    # Start in a new terminal
    gnome-terminal --disable-factory -- /bin/bash -c "${AGENT_MONGO_FOLDER}/agent_mongo" &
fi

# ======================= Start COSMOS Web =======================
echo "Starting npm..."
npm start --prefix ${COSMOS_WEB_FOLDER} &

# ================================================================

# Wait for processes to finish
wait

