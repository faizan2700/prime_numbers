#!/bin/bash

# Step 1: Add all changes to staging
git add .

# Step 2: Commit with a message
# You can pass the commit message as an argument to the script like this: ./push_to_github.sh "Your commit message"
commit_message="$1"
if [ -z "$commit_message" ]; then
    echo "Commit message is required. Example: ./push_to_github.sh \"Your commit message\""
    exit 1
fi

git commit -m "$commit_message"

# Step 3: Push to the master branch
git push -u origin master

