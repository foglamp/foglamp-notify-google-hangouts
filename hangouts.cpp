/*
 * FogLAMP Google hangouts notification delivery plugin.
 *
 * Copyright (c) 2019 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch           
 */
#include "hangouts.h"
#include <logger.h>
#include <simple_https.h>
#include <rapidjson/document.h>

using namespace std;
using namespace rapidjson;


/**
 * Construct a hangouts notification plugin
 *
 * @param category	The configuration of the plugin
 */
Hangouts::Hangouts(ConfigCategory *category)
{
	m_url = category->getValue("webhook");
	m_text = category->getValue("text");
}

/**
 * The destructure for the hangouts plugin
 */
Hangouts::~Hangouts()
{
}

/**
 * Send a notification via the Hangouts webhook
 *
 * @param notificationName 	The name of this notification
 * @param triggerReason		Why the notification is being sent
 * @param message		The message to send
 */
void Hangouts::notify(const string& notificationName, const string& triggerReason, const string& message)
{
ostringstream   payload;
SimpleHttps	*https;


	payload << "{ \"text\" : \"";
	payload << "*" << notificationName << "*\\n\\n";
	payload << message << "\\n";
	Document doc;
	doc.Parse(triggerReason.c_str());
	if (!doc.HasParseError() && doc.HasMember("reason"))
	{
		payload << "Notification has " << doc["reason"].GetString() << "\\n\\n";
	}
	payload << m_text << "\\n\\n";
	payload << "\" }";

	std::vector<std::pair<std::string, std::string>> headers;
	pair<string, string> header = make_pair("Content-type", "application/json");
	headers.push_back(header);

	/**
	 * Extract host and port from URL
	 */
	size_t findProtocol = m_url.find_first_of(":");
	string protocol = m_url.substr(0,findProtocol);

	string tmpUrl = m_url.substr(findProtocol + 3);
	size_t findPort = tmpUrl.find_first_of(":");
	size_t findPath = tmpUrl.find_first_of("/");
	string port, hostName;
	if (findPort == string::npos)
	{
		hostName = tmpUrl.substr(0, findPath);
		https  = new SimpleHttps(hostName);
	}
	else
	{
		hostName = tmpUrl.substr(0, findPort);
		port = tmpUrl.substr(findPort + 1 , findPath - findPort -1);
		string hostAndPort(hostName + ":" + port);
		https  = new SimpleHttps(hostAndPort);
	}

	try
	{
		int errorCode;
		if ((errorCode = https->sendRequest("POST",
						    m_url,
						    headers,
						    payload.str())) != 200 &&
		    errorCode == 202)
		{
			Logger::getLogger()->error("Failed to send notification to "
						   "hangouts webhook %s, errorCode %d",
						   m_url.c_str(),
						   errorCode);
		}
	}
	catch (exception &e)
	{
		Logger::getLogger()->error("Exception while sending notification "
					   "to hangouts webhook %s: %s",
					    m_url.c_str(),
					    e.what());
	}
	delete https;
}

/**
 * Reconfigure the hangouts delivery plugin
 *
 * @param newConfig	The new configuration
 */
void Hangouts::reconfigure(const string& newConfig)
{
	ConfigCategory category("new", newConfig);
	m_url = category.getValue("webhook");
	m_text = category.getValue("text");
}
