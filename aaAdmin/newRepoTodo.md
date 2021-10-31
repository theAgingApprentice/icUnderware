# Todo list for new repo

This document contains a list of actions to take in order to set up a new Github repo using the IC Underwear repository as a template.

## Process Overview

1. Clone the https://github.com/theAgingApprentice/icUnderware repository.
2. Move/rename ./aaAdmin/platformio.ini.temp to ./platformio.ini.  
3. Create the standard Github labels.

## Create Github Labels
curl --data "name=feature&color=#5843AD" --header "PRIVATE-TOKEN: <your_access_token>" "https://github.com/theAgingApprentice/icUnderware/aaAdmin/labels.json"