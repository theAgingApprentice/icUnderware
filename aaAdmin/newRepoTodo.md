# Todo list for new repo

This document contains a list of actions to take once you have in order to set up a new Github repo using the IC Underwear repository as a template.

## Process Overview

1. Clone the https://github.com/theAgingApprentice/icUnderware repository.
2. Move/rename ./aaAdmin/platformio.ini.temp to ./platformio.ini.  
3. Curate the Github labels in the new repository.
## Make repo on Github
- Navigate to the Aging Apprentice template repo [here](https://github.com/theAgingApprentice/aaTemplate).
- Click the Use this template button.
- Follow the online instructions.
- Be sure to click the **include all branches** option.
- Invite new contributors if required to do the next steps. 
   - Go to your new Github repo with your browser.  
   - Settings/Manage Access/Invite a collaborator/enter name.
- Click on the **Code** button then click on the clipboard to copy the URL. 

## Make local repo
- Get into Visual Studio Code terminal window with no projects open.
- Navigate to the project folder on your local hard drive.
- Issue the command `git clone https://github.com/theAgingApprentice/{project name}` (you can paste the URL that you copied in the previous step)
- Navigate into the newly created directory `cd {project name}`
- Rename **template_platformio.ini_tmp** to **platformio.ini** in the root of your repo.
- Open project in PlatformIO.
   - Start Visual Studio Code. 
   - Start PlatformIO.
- Open project.
## Edit Doxyfile
There is a file called Doxyfile in the root of the repository. Make the following edits.
- PROJECT_NAME           = {project name}
- PROJECT_BRIEF          = "Brief explanation of what class does."
## Edit this README.md file
Update the readme file to reflect what your project is all about. 
## Curate Github Labels
```This process only works on unix systems. A windows script could be mae to do this on windos machines.```
In order to use our curated list of Github labels while managing tasks and pull requests do the following.
- Create a Github [personal access Token](https://github.com/settings/tokens). Be sure to select REPO scope. Save the token somewhere safe as you cannot find it again once you close the tab. 
- Navigate to the aaAdmin directory of the new local repository that you created.   
- In the bash shell script *updateGithubLabels*, change the targetGithubName value to your Github name.
- Make sure that the bash script is an executable (chmod u+x updateGithubLabels).
- Run the script: ./updateGithubLabels taregtRepoName githubPersonalToken 
- If all goes well you should see 
   - A bunch of messages scroll by in your terminal
   - In the issues tab of your code repoitory click the Labels button and you should see the curated list of labels. 
