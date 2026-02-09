#!/bin/bash
set -e
cd /tmp/bitchx-1.2.1/source/

echo "Applying Pigman v2 updates..."

# Copy cool.c happens before this script runs

# Patch commands.c
echo "Patching commands.c..."

# Check if PIGMAN is already there
if grep -q "PIGMAN" commands.c; then
    echo "Commands already patched."
else
    # Remove RAINBOW if present
    sed -i '/RAINBOW/d' commands.c
    
    # Add PIGMAN before QUIT
    # Note: Using a temporary file approach to be safe with multiline matching
    # Insert externs at top
    sed -i '1i extern void cool_pigman_cmd(char *, char *, char *, char *);' commands.c
    sed -i '1i extern void cool_wtf_cmd(char *, char *, char *, char *);' commands.c
    
    # Insert commands using awk for safety
    awk '/{ "QUIT",/ { print "\t{ \"PIGMAN\",\t\"Cool\",\t\tcool_pigman_cmd,\t0,\t\"Show Pigman\" },"; } { print }' commands.c > c.tmp && mv c.tmp commands.c
    awk '/{ "QUIT",/ { print "\t{ \"WTF\",\t\t\"Cool\",\t\tcool_wtf_cmd,\t0,\t\"Random quote\" },"; } { print }' commands.c > c.tmp && mv c.tmp commands.c
    
    echo "Added PIGMAN and WTF commands."
fi

# Clean build
echo "Rebuilding..."
gmake clean
gmake

# Install
echo "Installing..."
cd ..
sudo gmake install
