====================
Development workflow
====================

This document describes the details of development and git workflows.

Release
=======

This section describes the steps of a regular release.

Begin release
-------------

To begin a new regular release with *major*, *minor* and *patch* version numbers
``X``, ``Y`` and ``Z`` respectively, where the *minor* number typically gets
incremented by one, and push it to a ``git`` *remote* called ``origin``, do
the following:

::

  cd path/to/cloned/repository
  echo $(<VERSION) | if IFS=. read -r X Y Z
  then
    let Y++;
    git checkout develop
    git pull origin develop
    git checkout -b release-$X.$Y.$Z develop
    echo -n "$X.$Y.$Z" > VERSION
    git add VERSION
    git commit -m "Started release $X.$Y.$Z"
    git push origin release-$X.$Y.$Z
  fi

Finish release
--------------

To finish a current release with *major*, *minor* and *patch* version numbers
``X``, ``Y`` and ``Z`` respectively, merge it to the ``develop`` and ``main``
branches and push it to a ``git`` *remote* called ``origin``, do the following:

::

  cd path/to/cloned/repository
  echo $(<VERSION) | if IFS=. read -r X Y Z
  then
    git checkout release-$X.$Y.$Z || exit 1
    git pull origin release-$X.$Y.$Z 
    git checkout main
    git pull origin main
    git merge -X theirs --no-ff release-$X.$Y.$Z
    git tag -a $X.$Y.$Z -m "Tagged release $X.$Y.$Z"
    git checkout develop
    git pull origin develop
    git merge --no-ff release-$X.$Y.$Z
    git push origin $X.$Y.$Z
    git push origin main
    git push origin develop
    git push origin :release-$X.$Y.$Z
    git branch -D release-$X.$Y.$Z
  fi

Hot-fix
=======

This section describes the steps of a hot-fix release.

Begin hot-fix
-------------

To begin a new hot-fix release with *major*, *minor* and *patch* version numbers
``X``, ``Y`` and ``Z`` respectively, where the *patch* number typically gets
incremented by one, and push it to a ``git`` *remote* called ``origin``, do
the following:

::

  cd path/to/cloned/repository
  echo $(<VERSION) | if IFS=. read -r X Y Z
  then
    let Z++;
    git checkout main
    git pull origin main
    git checkout -b hotfix-$X.$Y.$Z $X.$Y.$((Z-1))^2
    echo -n "$X.$Y.$Z" > VERSION
    git add VERSION
    git commit -m "Started hotfix $X.$Y.$Z"
    git push origin hotfix-$X.$Y.$Z
  fi

Finish hot-fix
--------------

To finish a current hot-fix with *major*, *minor* and *patch* version numbers
``X``, ``Y`` and ``Z`` respectively, merge it to the ``develop`` and ``main``
branches and push it to a ``git`` *remote* called ``origin``, do the following:

::

  cd path/to/cloned/repository
  echo $(<VERSION) | if IFS=. read -r X Y Z
  then
    git checkout hotfix-$X.$Y.$Z || exit 1
    git pull origin hotfix-$X.$Y.$Z 
    git checkout main
    git pull origin main
    git merge -X theirs --no-ff hotfix-$X.$Y.$Z 
    git tag -a $X.$Y.$Z -m "Tagged hotfix $X.$Y.$Z"
    git checkout develop
    git pull origin develop
    git merge --no-ff hotfix-$X.$Y.$Z 
    git push origin $X.$Y.$Z
    git push origin main
    git push origin develop
    git push origin :hotfix-$X.$Y.$Z
    git branch -D hotfix-$X.$Y.$Z 
  fi

