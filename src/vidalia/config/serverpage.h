/****************************************************************
 *  Vidalia is distributed under the following license:
 *
 *  Copyright (C) 2006,  Matt Edman, Justin Hipple
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/

/** 
 * \file serverpage.h
 * \version $Id$
 * \brief Tor server configuration options
 */

#ifndef _SERVERPAGE_H
#define _SERVERPAGE_H

#include <QMessageBox>
#include <QTimer>
#include <torcontrol.h>
#include <serversettings.h>
#include <exitpolicy.h>
#include <helpbrowser.h>

#include "configpage.h"
#include "ui_serverpage.h"


class ServerPage : public ConfigPage
{
  Q_OBJECT

public:
  /** Default Constructor */
  ServerPage(QWidget *parent = 0);
  /** Default Destructor */
  ~ServerPage();
  /** Saves the changes on this page */
  bool save(QString &errmsg);
  /** Loads the settings for this page */
  void load();
  
  /** Applies the server configuration settings to Tor. Returns true if the
   * settings were applied successfully. Otherwise, <b>errmsg</b> is set and
   * false is returned. */
  bool apply(QString &errmsg);
  /** Reverts the server configuration settings to their values at the last
   * time they were successfully applied to Tor. */
  void revert();
  /** Returns true if the user has changed their server settings since the
   * last time they were applied to Tor. */
  bool changedSinceLastApply();

private slots:
  /** Called when the user toggles any one of the server mode radio buttons
   * and hides or displays the server configuration tabs appropriately. */
  void serverModeChanged(bool enabled);
  /** Called when the user clicks the bandwidth help button */
  void bandwidthHelp();
  /** Called when the user clicks the exit policy help button */
  void exitPolicyHelp();
	/** Called when the user selects a new value from the rate combo box */
	void rateChanged(int rate);
  /** Called when the user edits the max or average bandwidth limits. */
  void customRateChanged();
  /** Called when Vidalia has authenticated to Tor. If the user's Tor is not
   * recent enough, this disables the bridge server option and displays a
   * warning if the user had previously configured Tor as a bridge. */
  void onAuthenticated();
  /** Called when Vidalia disconnects from Tor. This method reenables the
   * bridge server option. */
  void onDisconnected();
  /** Copies the user's bridge relay identity to the clipboard. */
  void copyBridgeIdentity();

private:
  /** Index values of rate values in the bandwidth limits dropdown box. */
  enum BwRateIndex {
    CableDsl256 = 0, /**< Cable/DSL 256 Kbps */
    CableDsl512,     /**< Cable/DSL 512 Kbps */
    CableDsl768,     /**< Cable/DSL 768 Kbps */
    T1CableDsl1500,  /**< T1/Cable/DSL 1.5 Mbps */
    GreaterThan1500, /**< > 1.5 Mbps */
    CustomBwLimits   /**< Custom bandwidth limits */
  };
  
  /** Returns the index of the selected item in lstExitPolicies */
  int selectedIndex();
  
  /** Saves the server's bandwidth average and burst limits. */
  void saveBandwidthLimits();
  /** Loads the server's bandwidth average and burst limits. */
  void loadBandwidthLimits();
  /** Saves the server's exit policies. */
  void saveExitPolicies();
  /** Loads the server's exit policies. */
  void loadExitPolicies();
  /** Loads the user's bridge relay identity into the appropriate widgets. If
   *  the user's bridge is not running, then "Not Running" will be
   *  displayed. Otherwise, either the bridge's "address:port", "fingerprint",
   *  or "address:port fingerprint" will be displayed, depending on whether
   *  our GETCONF and GETINFO commands are successful. */
  void loadBridgeIdentity();

  /** A ServerSettings object used to get and set information about how a
   * local Tor server is configured. */
  ServerSettings*  _settings;

  /** Qt Designer generated object */
  Ui::ServerPage ui;
};

#endif
