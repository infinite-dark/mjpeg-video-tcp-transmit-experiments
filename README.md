# JPEG Webcam Streaming via TCP (but not really)

These are some of the codes that I wrote while experimenting with video streaming over the network. I tried to reach a 720p@30 transmission on a single board computer. For a long time it had been much easier to write code that brute-forces JPEGs through a TCP socket than to come up with the right GStreamer pipeline and this repo is the result. I used OpenCV, SDL/pygame, and the standard libraries.

Copyright Notice - Important
---
Please note, while I strive to respect all legal obligations, I am not a legal expert and therefore I am unable to properly address the licensing and other legal issues potentially concerning this repo.

  - Author: The code present in this repository was written by me based on publicly available information and documentations.
  - Licensing: The respective licenses of the used components apply (in whatever way the law says they should I guess? I dunno, don't ask me.). Just respect the licenses...
  - Purpose: This project was made for my own, personal, educational use.
  - Property and Rights: I do not own any rights to the used libraries or other software components (in part or as a whole) used in this project.
  - Usage: The software is NOT INTENDED for use in any way WHATSOEVER. I do NOT provide any warranty for the software and disclaim any liability for its use.

My intention for publishing this project on GitHub was purely technical - to share the code without resorting to manually adding project collaborators. The problem is that GitHub doesn't allow for "unlisted" repositories in the same way as, for example, YouTube allows for "unlisted" videos. I'm therefore forced to publish the repo even if I do not want to do that whatsoever (especially considering the legal issues).
