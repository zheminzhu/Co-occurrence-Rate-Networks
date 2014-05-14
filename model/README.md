




<!DOCTYPE html>
<html class="   ">
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# object: http://ogp.me/ns/object# article: http://ogp.me/ns/article# profile: http://ogp.me/ns/profile#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    
    
    <title>Co-occurrence-Rate-Networks/README.md at master · zheminzhu/Co-occurrence-Rate-Networks</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <meta property="fb:app_id" content="1401488693436528"/>

      <meta content="@github" name="twitter:site" /><meta content="summary" name="twitter:card" /><meta content="zheminzhu/Co-occurrence-Rate-Networks" name="twitter:title" /><meta content="Co-occurrence-Rate-Networks - Co-occurrence Rate Networks for Sequence Labeling" name="twitter:description" /><meta content="https://avatars1.githubusercontent.com/u/7154405?s=400" name="twitter:image:src" />
<meta content="GitHub" property="og:site_name" /><meta content="object" property="og:type" /><meta content="https://avatars1.githubusercontent.com/u/7154405?s=400" property="og:image" /><meta content="zheminzhu/Co-occurrence-Rate-Networks" property="og:title" /><meta content="https://github.com/zheminzhu/Co-occurrence-Rate-Networks" property="og:url" /><meta content="Co-occurrence-Rate-Networks - Co-occurrence Rate Networks for Sequence Labeling" property="og:description" />

    <link rel="assets" href="https://assets-cdn.github.com/">
    <link rel="conduit-xhr" href="https://ghconduit.com:25035/">
    <link rel="xhr-socket" href="/_sockets" />

    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="collector-cdn.github.com" name="octolytics-script-host" /><meta content="github" name="octolytics-app-id" /><meta content="82590CB9:5507:FA9F61:53737B55" name="octolytics-dimension-request_id" /><meta content="7154405" name="octolytics-actor-id" /><meta content="zheminzhu" name="octolytics-actor-login" /><meta content="985b13f45865437ab93511512a78a4221d825fbf1d5dc0a26b0392daecce6220" name="octolytics-actor-hash" />
    

    
    
    <link rel="icon" type="image/x-icon" href="https://assets-cdn.github.com/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="tuDhaAno0zv50G1pMoIonoTiealU0hnaXs8J7fKEBBwrJ7UNlhVzaLgNo9z4i39LTw2UDy8vB65m+RqwalWz1Q==" name="csrf-token" />

    <link href="https://assets-cdn.github.com/assets/github-08eca722f10c5a963656d215e35a809b85c86d1e.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://assets-cdn.github.com/assets/github2-2dd00e4d2cf7d1f9ae9a7ba0dd87a4eed741de32.css" media="all" rel="stylesheet" type="text/css" />
    


    <meta http-equiv="x-pjax-version" content="8f882ae42120fd172a3d81adab0f2690">

      
  <meta name="description" content="Co-occurrence-Rate-Networks - Co-occurrence Rate Networks for Sequence Labeling" />

  <meta content="7154405" name="octolytics-dimension-user_id" /><meta content="zheminzhu" name="octolytics-dimension-user_login" /><meta content="19734804" name="octolytics-dimension-repository_id" /><meta content="zheminzhu/Co-occurrence-Rate-Networks" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="19734804" name="octolytics-dimension-repository_network_root_id" /><meta content="zheminzhu/Co-occurrence-Rate-Networks" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/zheminzhu/Co-occurrence-Rate-Networks/commits/master.atom" rel="alternate" title="Recent Commits to Co-occurrence-Rate-Networks:master" type="application/atom+xml" />

  </head>


  <body class="logged_in  env-production linux vis-public page-blob">
    <a href="#start-of-content" tabindex="1" class="accessibility-aid js-skip-to-content">Skip to content</a>
    <div class="wrapper">
      
      
      
      


      <div class="header header-logged-in true">
  <div class="container clearfix">

    <a class="header-logo-invertocat" href="https://github.com/">
  <span class="mega-octicon octicon-mark-github"></span>
</a>

    
    <a href="/notifications" aria-label="You have no unread notifications" class="notification-indicator tooltipped tooltipped-s" data-hotkey="g n">
        <span class="mail-status all-read"></span>
</a>

      <div class="command-bar js-command-bar  in-repository">
          <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<div class="commandbar">
  <span class="message"></span>
  <input type="text" data-hotkey="s, /" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    data-username="zheminzhu"
      data-repo="zheminzhu/Co-occurrence-Rate-Networks"
      data-branch="master"
      data-sha="c962836daefa8f86cd92cdf79a2520386a3ca613"
  >
  <div class="display hidden"></div>
</div>

    <input type="hidden" name="nwo" value="zheminzhu/Co-occurrence-Rate-Networks" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target" role="button" aria-haspopup="true">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container" aria-hidden="true">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="help tooltipped tooltipped-s" aria-label="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
        <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
            <li><a href="https://gist.github.com">Gist</a></li>
            <li><a href="/blog">Blog</a></li>
          <li><a href="https://help.github.com">Help</a></li>
        </ul>
      </div>

    


  <ul id="user-links">
    <li>
      <a href="/zheminzhu" class="name">
        <img alt="zheminzhu" class=" js-avatar" data-user="7154405" height="20" src="https://avatars2.githubusercontent.com/u/7154405?s=140" width="20" /> zheminzhu
      </a>
    </li>

    <li class="new-menu dropdown-toggle js-menu-container">
      <a href="#" class="js-menu-target tooltipped tooltipped-s" aria-label="Create new...">
        <span class="octicon octicon-plus"></span>
        <span class="dropdown-arrow"></span>
      </a>

      <div class="new-menu-content js-menu-content">
      </div>
    </li>

    <li>
      <a href="/settings/profile" id="account_settings"
        class="tooltipped tooltipped-s"
        aria-label="Account settings ">
        <span class="octicon octicon-tools"></span>
      </a>
    </li>
    <li>
      <form class="logout-form" action="/logout" method="post">
        <button class="sign-out-button tooltipped tooltipped-s" aria-label="Sign out">
          <span class="octicon octicon-log-out"></span>
        </button>
      </form>
    </li>

  </ul>

<div class="js-new-dropdown-contents hidden">
  

<ul class="dropdown-menu">
  <li>
    <a href="/new"><span class="octicon octicon-repo-create"></span> New repository</a>
  </li>
  <li>
    <a href="/organizations/new"><span class="octicon octicon-organization"></span> New organization</a>
  </li>


    <li class="section-title">
      <span title="zheminzhu/Co-occurrence-Rate-Networks">This repository</span>
    </li>
      <li>
        <a href="/zheminzhu/Co-occurrence-Rate-Networks/issues/new"><span class="octicon octicon-issue-opened"></span> New issue</a>
      </li>
      <li>
        <a href="/zheminzhu/Co-occurrence-Rate-Networks/settings/collaboration"><span class="octicon octicon-person-add"></span> New collaborator</a>
      </li>
</ul>

</div>


    
  </div>
</div>

      

        



      <div id="start-of-content" class="accessibility-aid"></div>
          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    <div id="js-flash-container">
      
    </div>
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        

<ul class="pagehead-actions">

    <li class="subscription">
      <form accept-charset="UTF-8" action="/notifications/subscribe" class="js-social-container" data-autosubmit="true" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="OHuRFUZbaspbdJ+sDwXapiMEdsbu+mG4zT5Aa3D0jx8zUaIp4kEhviTqIHE9zo6Tj1/ZMkMqUmg9r7CXHho8Gw==" /></div>  <input id="repository_id" name="repository_id" type="hidden" value="19734804" />

    <div class="select-menu js-menu-container js-select-menu">
      <a class="social-count js-social-count" href="/zheminzhu/Co-occurrence-Rate-Networks/watchers">
        1
      </a>
      <span class="minibutton select-menu-button with-count js-menu-target" role="button" tabindex="0" aria-haspopup="true">
        <span class="js-select-button">
          <span class="octicon octicon-eye-unwatch"></span>
          Unwatch
        </span>
      </span>

      <div class="select-menu-modal-holder">
        <div class="select-menu-modal subscription-menu-modal js-menu-content" aria-hidden="true">
          <div class="select-menu-header">
            <span class="select-menu-title">Notification status</span>
            <span class="octicon octicon-remove-close js-menu-close"></span>
          </div> <!-- /.select-menu-header -->

          <div class="select-menu-list js-navigation-container" role="menu">

            <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_included" name="do" type="radio" value="included" />
                <h4>Not watching</h4>
                <span class="description">You only receive notifications for conversations in which you participate or are @mentioned.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye-watch"></span>
                  Watch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item selected" role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input checked="checked" id="do_subscribed" name="do" type="radio" value="subscribed" />
                <h4>Watching</h4>
                <span class="description">You receive notifications for all conversations in this repository.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye-unwatch"></span>
                  Unwatch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_ignore" name="do" type="radio" value="ignore" />
                <h4>Ignoring</h4>
                <span class="description">You do not receive any notifications for conversations in this repository.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-mute"></span>
                  Stop ignoring
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

          </div> <!-- /.select-menu-list -->

        </div> <!-- /.select-menu-modal -->
      </div> <!-- /.select-menu-modal-holder -->
    </div> <!-- /.select-menu -->

</form>
    </li>

  <li>
  

  <div class="js-toggler-container js-social-container starring-container ">

    <form accept-charset="UTF-8" action="/zheminzhu/Co-occurrence-Rate-Networks/unstar" class="js-toggler-form starred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="+tmcchWR3LqcrKafCYRN0LBguRrYTZdR7X001uPlYWwDwarSXGysUvqetSb1lu3eHJkTZvE/WlQxbwBEWoPW6Q==" /></div>
      <button
        class="minibutton with-count js-toggler-target star-button"
        aria-label="Unstar this repository" title="Unstar zheminzhu/Co-occurrence-Rate-Networks">
        <span class="octicon octicon-star-delete"></span><span class="text">Unstar</span>
      </button>
        <a class="social-count js-social-count" href="/zheminzhu/Co-occurrence-Rate-Networks/stargazers">
          0
        </a>
</form>
    <form accept-charset="UTF-8" action="/zheminzhu/Co-occurrence-Rate-Networks/star" class="js-toggler-form unstarred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="q6HHxsLsUyMDVqdM0Csh0MrXtDWS00YruQqAeLD9uwwffuZPuV9zjhGwveeFIWpj7U3Iw35czbV9/9Q++utpvw==" /></div>
      <button
        class="minibutton with-count js-toggler-target star-button"
        aria-label="Star this repository" title="Star zheminzhu/Co-occurrence-Rate-Networks">
        <span class="octicon octicon-star"></span><span class="text">Star</span>
      </button>
        <a class="social-count js-social-count" href="/zheminzhu/Co-occurrence-Rate-Networks/stargazers">
          0
        </a>
</form>  </div>

  </li>


        <li>
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/fork" class="minibutton with-count js-toggler-target fork-button lighter tooltipped-n" title="Fork your own copy of zheminzhu/Co-occurrence-Rate-Networks to your account" aria-label="Fork your own copy of zheminzhu/Co-occurrence-Rate-Networks to your account" rel="nofollow" data-method="post">
            <span class="octicon octicon-git-branch-create"></span><span class="text">Fork</span>
          </a>
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/network" class="social-count">0</a>
        </li>


</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="repo-label"><span>public</span></span>
          <span class="mega-octicon octicon-repo"></span>
          <span class="author"><a href="/zheminzhu" class="url fn" itemprop="url" rel="author"><span itemprop="title">zheminzhu</span></a></span><!--
       --><span class="path-divider">/</span><!--
       --><strong><a href="/zheminzhu/Co-occurrence-Rate-Networks" class="js-current-repository js-repo-home-link">Co-occurrence-Rate-Networks</a></strong>

          <span class="page-context-loader">
            <img alt="Octocat-spinner-32" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">
      <div class="repository-with-sidebar repo-container new-discussion-timeline js-new-discussion-timeline  ">
        <div class="repository-sidebar clearfix">
            

<div class="sunken-menu vertical-right repo-nav js-repo-nav js-repository-container-pjax js-octicon-loaders">
  <div class="sunken-menu-contents">
    <ul class="sunken-menu-group">
      <li class="tooltipped tooltipped-w" aria-label="Code">
        <a href="/zheminzhu/Co-occurrence-Rate-Networks" aria-label="Code" class="selected js-selected-navigation-item sunken-menu-item" data-hotkey="g c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches /zheminzhu/Co-occurrence-Rate-Networks">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

        <li class="tooltipped tooltipped-w" aria-label="Issues">
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/issues" aria-label="Issues" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g i" data-selected-links="repo_issues /zheminzhu/Co-occurrence-Rate-Networks/issues">
            <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
            <span class='counter'>0</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>

      <li class="tooltipped tooltipped-w" aria-label="Pull Requests">
        <a href="/zheminzhu/Co-occurrence-Rate-Networks/pulls" aria-label="Pull Requests" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g p" data-selected-links="repo_pulls /zheminzhu/Co-occurrence-Rate-Networks/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class='counter'>0</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


        <li class="tooltipped tooltipped-w" aria-label="Wiki">
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/wiki" aria-label="Wiki" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g w" data-selected-links="repo_wiki /zheminzhu/Co-occurrence-Rate-Networks/wiki">
            <span class="octicon octicon-book"></span> <span class="full-word">Wiki</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>
    </ul>
    <div class="sunken-menu-separator"></div>
    <ul class="sunken-menu-group">

      <li class="tooltipped tooltipped-w" aria-label="Pulse">
        <a href="/zheminzhu/Co-occurrence-Rate-Networks/pulse" aria-label="Pulse" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="pulse /zheminzhu/Co-occurrence-Rate-Networks/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped tooltipped-w" aria-label="Graphs">
        <a href="/zheminzhu/Co-occurrence-Rate-Networks/graphs" aria-label="Graphs" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="repo_graphs repo_contributors /zheminzhu/Co-occurrence-Rate-Networks/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped tooltipped-w" aria-label="Network">
        <a href="/zheminzhu/Co-occurrence-Rate-Networks/network" aria-label="Network" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-selected-links="repo_network /zheminzhu/Co-occurrence-Rate-Networks/network">
          <span class="octicon octicon-git-branch"></span> <span class="full-word">Network</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>
    </ul>


      <div class="sunken-menu-separator"></div>
      <ul class="sunken-menu-group">
        <li class="tooltipped tooltipped-w" aria-label="Settings">
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/settings" aria-label="Settings" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="repo_settings /zheminzhu/Co-occurrence-Rate-Networks/settings">
            <span class="octicon octicon-tools"></span> <span class="full-word">Settings</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>
      </ul>
  </div>
</div>

              <div class="only-with-full-nav">
                

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=push">
  <h3><strong>HTTPS</strong> clone URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/zheminzhu/Co-occurrence-Rate-Networks.git" readonly="readonly">
    <span class="url-box-clippy">
    <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/zheminzhu/Co-occurrence-Rate-Networks.git" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="ssh"
  data-url="/users/set_protocol?protocol_selector=ssh&amp;protocol_type=push">
  <h3><strong>SSH</strong> clone URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="git@github.com:zheminzhu/Co-occurrence-Rate-Networks.git" readonly="readonly">
    <span class="url-box-clippy">
    <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="git@github.com:zheminzhu/Co-occurrence-Rate-Networks.git" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=push">
  <h3><strong>Subversion</strong> checkout URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/zheminzhu/Co-occurrence-Rate-Networks" readonly="readonly">
    <span class="url-box-clippy">
    <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/zheminzhu/Co-occurrence-Rate-Networks" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>


<p class="clone-options">You can clone with
      <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>,
      <a href="#" class="js-clone-selector" data-protocol="ssh">SSH</a>,
      or <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>.
  <span class="help tooltipped tooltipped-n" aria-label="Get help on which URL is right for you.">
    <a href="https://help.github.com/articles/which-remote-url-should-i-use">
    <span class="octicon octicon-question"></span>
    </a>
  </span>
</p>



                <a href="/zheminzhu/Co-occurrence-Rate-Networks/archive/master.zip"
                   class="minibutton sidebar-button"
                   aria-label="Download zheminzhu/Co-occurrence-Rate-Networks as a zip file"
                   title="Download zheminzhu/Co-occurrence-Rate-Networks as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
              </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          


<a href="/zheminzhu/Co-occurrence-Rate-Networks/blob/eef0be0f2033575c1721601789e614444dbd0085/README.md" class="hidden js-permalink-shortcut" data-hotkey="y">Permalink</a>

<!-- blob contrib key: blob_contributors:v21:1a3341bed37b6ce6227fe6329b5cf9e4 -->

<p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

<a href="/zheminzhu/Co-occurrence-Rate-Networks/find/master" data-pjax data-hotkey="t" class="js-show-file-finder" style="display:none">Show File Finder</a>

<div class="file-navigation">
  

<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target" data-hotkey="w"
    data-master-branch="master"
    data-ref="master"
    role="button" aria-label="Switch branches or tags" tabindex="0" aria-haspopup="true">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button">master</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax aria-hidden="true">

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-remove-close js-menu-close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Find or create a branch…" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Find or create a branch…">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/zheminzhu/Co-occurrence-Rate-Networks/blob/master/README.md"
                 data-name="master"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target"
                 title="master">master</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <form accept-charset="UTF-8" action="/zheminzhu/Co-occurrence-Rate-Networks/branches" class="js-create-branch select-menu-item select-menu-new-item-form js-navigation-item js-new-item-form" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="iGJqpAl33iFHVIkZUEaGTrmqUxq4pAUt3RYaXifKihuVAGGHGktXbGxP565shemsaHSWmyEZpkblUcahqfYx2w==" /></div>
            <span class="octicon octicon-git-branch-create select-menu-item-icon"></span>
            <div class="select-menu-item-text">
              <h4>Create branch: <span class="js-new-item-name"></span></h4>
              <span class="description">from ‘master’</span>
            </div>
            <input type="hidden" name="name" id="name" class="js-new-item-value">
            <input type="hidden" name="branch" id="branch" value="master" />
            <input type="hidden" name="path" id="path" value="README.md" />
          </form> <!-- /.select-menu-item -->

      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/zheminzhu/Co-occurrence-Rate-Networks" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">Co-occurrence-Rate-Networks</span></a></span></span><span class="separator"> / </span><strong class="final-path">README.md</strong> <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="README.md" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
  </div>
</div>


  <div class="commit file-history-tease">
      <img alt="zheminzhu" class="main-avatar js-avatar" data-user="7154405" height="24" src="https://avatars2.githubusercontent.com/u/7154405?s=140" width="24" />
      <span class="author"><a href="/zheminzhu" rel="author">zheminzhu</a></span>
      <time class="js-relative-date" data-title-format="YYYY-MM-DD HH:mm:ss" datetime="2014-05-14T16:07:10+02:00" title="2014-05-14 16:07:10">May 14, 2014</time>
      <div class="commit-title">
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/commit/eef0be0f2033575c1721601789e614444dbd0085" class="message" data-pjax="true" title="Update README.md">Update README.md</a>
      </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>1</strong>  contributor</a></p>
      
    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2 class="facebox-header">Users who have contributed to this file</h2>
      <ul class="facebox-user-list">
          <li class="facebox-user-list-item">
            <img alt="zheminzhu" class=" js-avatar" data-user="7154405" height="24" src="https://avatars2.githubusercontent.com/u/7154405?s=140" width="24" />
            <a href="/zheminzhu">zheminzhu</a>
          </li>
      </ul>
    </div>
  </div>

<div class="file-box">
  <div class="file">
    <div class="meta clearfix">
      <div class="info file-name">
        <span class="icon"><b class="octicon octicon-file-text"></b></span>
        <span class="mode" title="File Mode">file</span>
        <span class="meta-divider"></span>
          <span>43 lines (31 sloc)</span>
          <span class="meta-divider"></span>
        <span>1.93 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
                <a class="minibutton js-update-url-with-hash"
                   href="/zheminzhu/Co-occurrence-Rate-Networks/edit/master/README.md"
                   data-method="post" rel="nofollow" data-hotkey="e">Edit</a>
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/raw/master/README.md" class="button minibutton " id="raw-url">Raw</a>
            <a href="/zheminzhu/Co-occurrence-Rate-Networks/blame/master/README.md" class="button minibutton js-update-url-with-hash">Blame</a>
          <a href="/zheminzhu/Co-occurrence-Rate-Networks/commits/master/README.md" class="button minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->

            <a class="minibutton danger empty-icon"
               href="/zheminzhu/Co-occurrence-Rate-Networks/delete/master/README.md"
               data-method="post" data-test-id="delete-blob-file" rel="nofollow">

          Delete
        </a>
      </div><!-- /.actions -->
    </div>
      
  <div id="readme" class="blob instapaper_body">
    <article class="markdown-body entry-content" itemprop="mainContentOfPage"><h1>
<a name="user-content-co-occurrence-rate-networks" class="anchor" href="#co-occurrence-rate-networks"><span class="octicon octicon-link"></span></a>Co-occurrence-Rate-Networks</h1>

<p>Co-occurrence Rate Networks for Sequence Labeling</p>

<p><em>This version is only for verifying the results in the submitted paper. All the rights of datasets are reserved to their original authors. A more mature version will come soon.</em></p>

<h3>
<a name="user-content-introduction" class="anchor" href="#introduction"><span class="octicon octicon-link"></span></a>Introduction</h3>

<p>Co-occurrence rate networks are for sequence labelling tasks, such as named entity recognition, part-of-speech tagging … The applications of this software are similar to CRF (<a href="http://crfpp.googlecode.com/svn/trunk/doc/index.html">http://crfpp.googlecode.com/svn/trunk/doc/index.html</a>). But CRN can be trained much faster and obtain very competitive results.</p>

<h3>
<a name="user-content-system-and-compiler" class="anchor" href="#system-and-compiler"><span class="octicon octicon-link"></span></a>System and Compiler</h3>

<p>The Ubuntu 12.04 and gcc 4.7.3 are used for compiling the software. We do not know  if this works on other systems. If your gcc is old version, you can update it using these steps to gcc 4.7.3.</p>

<ol class="task-list">
<li> sudo add-apt-repository ppa:ubuntu-toolchain-r/test </li>
<li> sudo apt-get update </li>
<li> sudo apt-get install gcc-4.7</li>
<li> sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.6 </li>
<li> sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.7 40 --slave /usr/bin/g++ g++ /usr/bin/g++-4.7 </li>
<li> sudo update-alternatives --config gcc</li>
</ol><h3>
<a name="user-content-installation" class="anchor" href="#installation"><span class="octicon octicon-link"></span></a>Installation</h3>

<ol class="task-list">
<li> go to 'crn-0.1/'</li>
<li> sudo make</li>
</ol><h3>
<a name="user-content-usage" class="anchor" href="#usage"><span class="octicon octicon-link"></span></a>Usage</h3>

<ol class="task-list">
<li> ./train train_file template_file model_folder</li>
<li> ./decode model_folder test_file result_file</li>
</ol><h3>
<a name="user-content-the-following-three-steps-can-be-used-to-reproducing-the-results-in-the-paper-on-ner-datasets" class="anchor" href="#the-following-three-steps-can-be-used-to-reproducing-the-results-in-the-paper-on-ner-datasets"><span class="octicon octicon-link"></span></a>The following three steps can be used to reproducing the results in the paper on NER datasets:</h3>

<ol class="task-list">
<li> ./train ./data/ner_en.train ./data/ner.template ./model/</li>
<li> ./decode ./model/ ./data/ner_en.testa testa.result</li>
<li> ./decode ./model/ ./data/ner_en.testb testb.result</li>
</ol><h3>
<a name="user-content-data-format" class="anchor" href="#data-format"><span class="octicon octicon-link"></span></a>Data Format</h3>

<p>Training and decoding data has the same format, see examples in the ./data. </p>

<h3>
<a name="user-content-template-format" class="anchor" href="#template-format"><span class="octicon octicon-link"></span></a>Template Format</h3>

<p>See example in the ./data for the template format.</p>

<h3>
<a name="user-content-contact" class="anchor" href="#contact"><span class="octicon octicon-link"></span></a>Contact</h3>

<ul class="task-list">
<li>Zhemin Zhu (<a href="mailto:zhuzhemin@gmail.com">zhuzhemin@gmail.com</a>, <a href="mailto:z.zhu@utwente.nl">z.zhu@utwente.nl</a>)</li>
<li>Djoerd Hiemstra (<a href="mailto:d.hiemstra@utwente.nl">d.hiemstra@utwente.nl</a>)</li>
</ul></article>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/">
      <span class="mega-octicon octicon-mark-github" title="GitHub"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2014 <span title="0.04852s from github-fe127-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="fullscreen-contents js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped tooltipped-w" aria-label="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped tooltipped-w"
      aria-label="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-remove-close close js-ajax-error-dismiss"></a>
      Something went wrong with that request. Please try again.
    </div>


      <script crossorigin="anonymous" src="https://assets-cdn.github.com/assets/frameworks-5a921ce2c45d4a5235b8f9c5c716611df0a83a79.js" type="text/javascript"></script>
      <script async="async" crossorigin="anonymous" src="https://assets-cdn.github.com/assets/github-71380a7260f8593a61c90ab35f6f6cf70e28aaba.js" type="text/javascript"></script>
      
      
  </body>
</html>

