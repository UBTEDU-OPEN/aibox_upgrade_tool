/*
* Copyright (c) 2016, 深圳市优必选科技有限公司
* All rights reserved.
*
* 文件名称：IniConfig.h
* 创建时间：2016/11/15
* 文件标识：
* 文件摘要：IniConfig参数设置
*
* 当前版本：1.0.0.0
* 作    者：asu
* 完成时间：2016/11/15
* 版本摘要：
*/

#include "ciniconfig.h"


#include <QSettings>


const QString SETTING_SPLIT_CHART = "/";

//Config Node
const QString CFG_NODE_NAME_CONFIG = "Config";  //动作表路径配置节名
const QString CFG_KEY_NAME_ACT_PATH = "ActPath";  //动作表路径配置键名
const QString CFG_KEY_NAME_SERVER = "Server";  //服务器地址配置键名
const QString CFG_KEY_NAME_SERVER_UPDATE_ROBOT = "ServerUpdateRobot";  //服务器地址配置键名, only using for update robot ALPHA1E
const QString CFG_KEY_NAME_SERVER_WEB_IP = "ServerWebIp";
const QString CFG_KEY_NAME_SERVER_ENVIRONMENT = "Environment";
const QString CFG_KEY_NAME_SERVER_USED_FLAG = "UsedFlag";

const QString CFG_KEY_NAME_BIG_FRAME_DELAY = "BigFrameDelay";
const QString CFG_KEY_NAME_SMALL_FRAME_DELAY = "SmallFrameDelay";


//UserInfo Node
const QString CFG_NODE_NAME_USER_INFO = "UserInfo";  //用户信息节名
const QString CFG_KEY_NAME_USER_LOGIN_TYPE_PHONE_LOGIN = "PhoneLogin"; // 手机登录方式
const QString CFG_KEY_NAME_USER_LOGIN_TYPE_MAIL_LOGIN = "MailLogin"; // 邮箱登录方式
const QString CFG_KEY_NAME_COUNTRY_CODE = "CountryCode";  // 国家码
const QString CFG_KEY_NAME_USER_NAME = "UserName";  //户名键名
const QString CFG_KEY_NAME_PASSWORD = "Password"; // 密码
const QString CFG_KEY_NAME_USER_TYPE = "UserType";  //用户类型键名
const QString CFG_KEY_NAME_IS_SAVE = "IsSave";    //是否保存键名

const QString CFG_KEY_MUSIC_PATH = "ImportMusicPath"; // 导入音乐文件路径
const QString CFG_KEY_PROJ_PATH = "OpenProjectPath";  // 打开工程路径

const QString CFG_KEY_USER_ID = "UserID";  //户名键名
const QString CFG_KEY_TOKEN = "Token";  //户名键名
const QString CFG_KEY_LOGIN_TYPE= "LoginType";  //户名键名





//node of [LanguageSetting]
const QString CFG_NODE_NAME_LANGUAGE_SETTING = "LanguageSetting";  //LanguageSetting节名
const QString CFG_KEY_NAME_LANGUAGE = "Language";  //键名

//node of [RobotTypeSetting]
const QString CFG_NODE_NAME_ROBOT_TYPE_SETTING = "RobotTypeSetting";  //RobotTypeSetting节名
const QString CFG_KEY_NAME_ROBOT_TYPE = "RobotType";  //键名


//node of [Aly oss]
const QString CFG_NODE_NAME_ALY_OSS = "AlyOss";  //AlyOss节名
const QString CFG_KEY_NAME_ACCESSKEYID = "AccessKeyId";  //键名
const QString CFG_KEY_NAME_ACCESSKEYSECRET = "AccessKeySecret";  //键名
const QString CFG_KEY_NAME_ENDPOINT = "Endpoint";  //键名
const QString CFG_KEY_NAME_BUCKETNAME= "BucketName";  //键名
const QString CFG_KEY_NAME_OBJECT_NAME = "ObjectName";  //键名
const QString CFG_KEY_NAME_EXPIRETIMESTAMP = "ExpireTimestamp";  //键名
const QString CFG_KEY_NAME_SECURITY_TOKEN = "SecurityToken";  //键名

const QString CFG_NODE_NAME_VERSION = "version";  //version节名
const QString CFG_KEY_NAME_WEB_VERSION = "webVersion";  //web版本
const QString CFG_KEY_NAME_WEB__VERSION_MD5 = "webVersionMd5";  //web版本 MD5
const QString CFG_KEY_NAME_MAIN_VERSION = "mainVersion";  //main版本
const QString CFG_KEY_NAME_MAIN_VERSION_MD5 = "mainVersionMd5";  // main版本 md5
const QString CFG_KEY_NAME_MAIN_IGNORE_VERSION = "ignoreVersion";  // 忽略的版本

const QString CFG_KEY_NAME_MAX_THREAD_COUNT = "maxThread";  // 最大线程数
const QString CFG_KEY_NAME_MAX_BUFF = "MaxBuff";  // 最大线程数


CIniConfig::CIniConfig()
{
    m_strConfigIniFilePath = "";
}

CIniConfig::~CIniConfig()
{

}

bool CIniConfig::setValue(const QString &strFile, const QString &strKey, const QVariant &varValue)
{
    QSettings settings(strFile, QSettings::IniFormat);
    settings.setValue(strKey, varValue);

    return true;
}

bool CIniConfig::getValue(const QString &strFile, const QString &strKey, int &nValue)
{
    QVariant var = CIniConfig::getValue(strFile, strKey);

    bool bOk = false;
    nValue = var.toInt(&bOk);

    return bOk;
}

bool CIniConfig::getValue(const QString &strFile, const QString &strKey, double &dValue)
{
    QVariant var = CIniConfig::getValue(strFile, strKey);

    bool bOk = false;
    dValue = var.toDouble(&bOk);

    return bOk;
}

bool CIniConfig::getValue(const QString &strFile, const QString &strKey, QString &strValue)
{
    QVariant var = CIniConfig::getValue(strFile, strKey);
    strValue = var.toString();

    return (!strValue.isEmpty());
}

bool CIniConfig::getValue(const QString &strFile, const QString &strKey, bool &bValue)
{
    QVariant var = CIniConfig::getValue(strFile, strKey);

    bValue = var.toBool();
    return bValue;
}

QString CIniConfig::getKey(const QString &strKeyPre, const QString &strKeySuffix)
{
    if(strKeyPre.endsWith(SETTING_SPLIT_CHART))
    {
        return strKeyPre + strKeySuffix;
    }

    return strKeyPre + SETTING_SPLIT_CHART + strKeySuffix;
}

QString CIniConfig::getKey(const QString &strKeyPre, const QString &strKeyMid, const QString &strKeySuffix)
{
    QString strTemp = CIniConfig::getKey(strKeyPre, strKeyMid);
    return CIniConfig::getKey(strTemp, strKeySuffix);
}

QVariant CIniConfig::getValue(const QString &strFile, const QString &strKey)
{
    QSettings settings(strFile, QSettings::IniFormat);
    return settings.value(strKey);
}


QString CIniConfig::getKeyNodeConfig()
{
    return CFG_NODE_NAME_CONFIG;
}

QString CIniConfig::getKeyNodeUserInfo()
{
    return CFG_NODE_NAME_USER_INFO;
}

QString CIniConfig::getKeyNodeLanguageSetting()
{
    return CFG_NODE_NAME_LANGUAGE_SETTING;
}

QString CIniConfig::getKeyNodeAlyOss()
{
    return CFG_NODE_NAME_ALY_OSS;
}

QString CIniConfig::getKeyAccessKeyId()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeAlyOss(),
                              CFG_KEY_NAME_ACCESSKEYID);
}

QString CIniConfig::getKeyAccessKeySecret()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeAlyOss(),
                              CFG_KEY_NAME_ACCESSKEYSECRET);
}

QString CIniConfig::getKeyEndpoint()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeAlyOss(),
                              CFG_KEY_NAME_ENDPOINT);
}

QString CIniConfig::getKeyBucketName()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeAlyOss(),
                              CFG_KEY_NAME_BUCKETNAME);
}

QString CIniConfig::getKeyObjectName()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeAlyOss(),
                              CFG_KEY_NAME_OBJECT_NAME);
}

QString CIniConfig::getKeySecurityToken()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeAlyOss(),
                              CFG_KEY_NAME_SECURITY_TOKEN);
}



QString CIniConfig::getKeyExpireTimestamp()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeAlyOss(),
                              CFG_KEY_NAME_EXPIRETIMESTAMP);
}




QString CIniConfig::getKeyLanguage()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeLanguageSetting(),
                              CFG_KEY_NAME_LANGUAGE);
}


QString CIniConfig::getKeyUserID()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeUserInfo(),
                              CFG_KEY_USER_ID);
}

QString CIniConfig::getKeyToken()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeUserInfo(),
                              CFG_KEY_TOKEN);
}

QString CIniConfig::getKeyLoginType()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeUserInfo(),
                              CFG_KEY_LOGIN_TYPE);
}

QString CIniConfig::getKeyNodeRobotTypeSetting()
{
    return CFG_NODE_NAME_ROBOT_TYPE_SETTING;
}

QString CIniConfig::getKeyRobotType()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeRobotTypeSetting(),
                              CFG_KEY_NAME_ROBOT_TYPE);
}

QString CIniConfig::getKeyNodeVersion()
{
    return CFG_NODE_NAME_VERSION;
}

QString CIniConfig::getKeyWebVersion()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeVersion(),
                              CFG_KEY_NAME_WEB_VERSION);
}

QString CIniConfig::getKeyWebVersionMd5()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeVersion(),
                              CFG_KEY_NAME_WEB__VERSION_MD5);
}

QString CIniConfig::getKeyMainVersion()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeVersion(),
                              CFG_KEY_NAME_MAIN_VERSION);
}

QString CIniConfig::getKeyMainVersionMd5()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeVersion(),
                              CFG_KEY_NAME_MAIN_VERSION_MD5);
}

QString CIniConfig::getKeyIgnoreVersion()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeVersion(),
                              CFG_KEY_NAME_MAIN_IGNORE_VERSION);
}

/**************************************************************************
* 函数名: getKeyMaxThreadCount
* 功能:获取最大线程数量key
* 参数: [@in]
* 参数: [@in]
* 返回值:QString
* 时间:2020/09/04
* 作者: Joker
*/
QString CIniConfig::getKeyMaxThreadCount()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                              CFG_KEY_NAME_MAX_THREAD_COUNT);

}

/**************************************************************************
* 函数名: getKeyMaxBuff
* 功能:获取最大传输buff
* 参数: [@in]
* 参数: [@in]
* 返回值:QString
* 时间:2020/09/04
* 作者: Joker
*/
QString CIniConfig::getKeyMaxBuff()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                              CFG_KEY_NAME_MAX_BUFF);

}



QString CIniConfig::getKeyActPath()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                                        CFG_KEY_NAME_ACT_PATH);
}

QString CIniConfig::getKeyServer()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                              CFG_KEY_NAME_SERVER);
}

//robot update 1e
QString CIniConfig::getKeyServerRobotUpdate()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                              CFG_KEY_NAME_SERVER_UPDATE_ROBOT);
}

QString CIniConfig::getKeyServerWebIp()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                              CFG_KEY_NAME_SERVER_WEB_IP);
}

QString CIniConfig::getKeyEnvironment()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                              CFG_KEY_NAME_SERVER_ENVIRONMENT);
}

QString CIniConfig::getKeyUsedFlag()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                              CFG_KEY_NAME_SERVER_USED_FLAG);
}



QString CIniConfig::getValueServerWebIp()
{
    QString strKey = CIniConfig::getKeyServerWebIp();
    QString strServerWebIp;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strServerWebIp);
    return strServerWebIp;
}

void CIniConfig::setValueServerWebIp(QString strIp)
{
    QString strKey = CIniConfig::getKeyServerWebIp();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strIp);
}

QString CIniConfig::getValueEnvironment()
{
    QString strKey = CIniConfig::getKeyEnvironment();
    QString strEnvironment;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strEnvironment);
    return strEnvironment;
}

void CIniConfig::setValueEnvironment(QString strEnvironment)
{
    QString strKey = CIniConfig::getKeyEnvironment();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strEnvironment);
}

QString CIniConfig::getValueUsedFlag()
{
    QString strKey = CIniConfig::getKeyUsedFlag();
    QString strUsedFlag;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strUsedFlag);
    return strUsedFlag;
}

void CIniConfig::setValueUsedFlag(QString strUsedFlag)
{
    QString strKey = CIniConfig::getKeyUsedFlag();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strUsedFlag);
}

QString CIniConfig::getWebVersion()
{
    QString strKey = CIniConfig::getKeyWebVersion();
    QString strWebVersion;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strWebVersion);
    return strWebVersion;
}

void CIniConfig::setWebVersion(QString strVersion)
{
    QString strKey = CIniConfig::getKeyWebVersion();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strVersion);
}

QString CIniConfig::getMainVersion()
{
    QString strKey = CIniConfig::getKeyMainVersion();
    QString strMainVersion;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strMainVersion);
    return strMainVersion;
}

void CIniConfig::setMainVersion(QString strVersion)
{
    QString strKey = CIniConfig::getKeyMainVersion();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strVersion);
}

QString CIniConfig::getMainVersionMd5()
{
    QString strKey = CIniConfig::getKeyMainVersionMd5();
    QString strMainVersionMd5;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strMainVersionMd5);
    return strMainVersionMd5;
}

void CIniConfig::setMainVersionMd5(QString strMd5)
{
    QString strKey = CIniConfig::getKeyMainVersionMd5();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strMd5);
}

QString CIniConfig::getWebVersionMd5()
{
    QString strKey = CIniConfig::getKeyWebVersionMd5();
    QString strWebVersionMd5;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strWebVersionMd5);
    return strWebVersionMd5;
}

void CIniConfig::setWebVersionMd5(QString strMd5)
{
    QString strKey = CIniConfig::getKeyWebVersionMd5();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strMd5);
}

QString CIniConfig::getIgnoreVersion()
{
    QString strKey = CIniConfig::getKeyIgnoreVersion();
    QString strIgnoreVersion;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strIgnoreVersion);
    return strIgnoreVersion;
}

void CIniConfig::setIgnoreVersion(QString strVersion)
{
    QString strKey = CIniConfig::getKeyIgnoreVersion();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strVersion);
}

/**************************************************************************
* 函数名: getMaxThreadCount
* 功能:获取最大线程数量
* 参数: [@in]
* 参数: [@in]
* 返回值:QString
* 时间:2020/09/04
* 作者: Joker
*/
QString CIniConfig::getMaxThreadCount()
{
    QString strKey = CIniConfig::getKeyMaxThreadCount();
    QString strMaxThreadCount;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strMaxThreadCount);
    return strMaxThreadCount;
}

/**************************************************************************
* 函数名: setMaxThreadCount
* 功能:设置最大线程数量
* 参数: [@in]strMaxThreadCount
* 参数: [@in]
* 返回值:QString
* 时间:2020/09/04
* 作者: Joker
*/
void CIniConfig::setMaxThreadCount(QString strMaxThreadCount)
{
    QString strKey = CIniConfig::getKeyMaxThreadCount();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strMaxThreadCount);
}

/**************************************************************************
* 函数名: getMaxBuff
* 功能:获取最大传输buff
* 参数: [@in]
* 参数: [@in]
* 返回值:QString
* 时间:2020/09/04
* 作者: Joker
*/
QString CIniConfig::getMaxBuff()
{
    QString strKey = CIniConfig::getKeyMaxBuff();
    QString strMaxBuff;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strMaxBuff);
    return strMaxBuff;
}

/**************************************************************************
* 函数名: setMaxBuff
* 功能:设置最大传输buff
* 参数: [@in]strMaxThreadCount
* 参数: [@in]
* 返回值:QString
* 时间:2020/09/04
* 作者: Joker
*/
void CIniConfig::setMaxBuff(QString strMaxBuff)
{
    QString strKey = CIniConfig::getKeyMaxBuff();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strMaxBuff);
}

QString CIniConfig::getKeyBigFrameDelay()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                                        CFG_KEY_NAME_BIG_FRAME_DELAY);
}

QString CIniConfig::getKeySmallFrameDelay()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeConfig(),
                                        CFG_KEY_NAME_SMALL_FRAME_DELAY);
}

QString CIniConfig::getKeyML()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeUserInfo(),
                              CFG_KEY_NAME_USER_LOGIN_TYPE_MAIL_LOGIN);
}

QString CIniConfig::getKeyPL()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeUserInfo(),
                              CFG_KEY_NAME_USER_LOGIN_TYPE_PHONE_LOGIN);
}

QString CIniConfig::getKeyMLUserName()
{
    return CIniConfig::getKey(CIniConfig::getKeyML(),
                              CFG_KEY_NAME_USER_NAME);
}

QString CIniConfig::getKeyMLPassword()
{
    return CIniConfig::getKey(CIniConfig::getKeyML(),
                              CFG_KEY_NAME_PASSWORD);
}

QString CIniConfig::getKeyMLUserType()
{
    return CIniConfig::getKey(CIniConfig::getKeyML(),
                              CFG_KEY_NAME_USER_TYPE);
}

QString CIniConfig::getKeyMLIsSave()
{
    return CIniConfig::getKey(CIniConfig::getKeyML(),
                              CFG_KEY_NAME_IS_SAVE);
}

QString CIniConfig::getKeyPLCountryCode()
{
    return CIniConfig::getKey(CIniConfig::getKeyPL(),
                              CFG_KEY_NAME_COUNTRY_CODE);
}

QString CIniConfig::getKeyPLUserName()
{
    return CIniConfig::getKey(CIniConfig::getKeyPL(),
                              CFG_KEY_NAME_USER_NAME);
}

QString CIniConfig::getKeyPLPassword()
{
    return CIniConfig::getKey(CIniConfig::getKeyPL(),
                              CFG_KEY_NAME_PASSWORD);
}

QString CIniConfig::getKeyPLUserType()
{
    return CIniConfig::getKey(CIniConfig::getKeyPL(),
                              CFG_KEY_NAME_USER_TYPE);
}

QString CIniConfig::getKeyPLIsSave()
{
    return CIniConfig::getKey(CIniConfig::getKeyPL(),
                              CFG_KEY_NAME_IS_SAVE);
}

QString CIniConfig::getKeyFilePath(emFilePathType eType)
{
    QString strKey = "";
    switch (eType) {
    case eFilePathImportMusic:
    {
        strKey = getKeyMusicPath();
        break;
    }
    case eFilePathOpenProject:
    {
        strKey = getKeyOpenProjPath();
        break;
    }
    default:
        break;
    }

    return strKey;
}

QString CIniConfig::getKeyMusicPath()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeUserInfo(),
                              CFG_KEY_MUSIC_PATH);
}

QString CIniConfig::getKeyOpenProjPath()
{
    return CIniConfig::getKey(CIniConfig::getKeyNodeUserInfo(),
                              CFG_KEY_PROJ_PATH);
}

bool CIniConfig::getValueActPath(QString &strValue)
{
    QString strKey = CIniConfig::getKeyActPath();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValueActPath(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyActPath();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

bool CIniConfig::getValueServer(QString &strValue)
{
    QString strKey = CIniConfig::getKeyServer();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValueServer(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyServer();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}
//robot 1e
bool CIniConfig::getValueServerRobotUpate(QString &strValue)
{
    QString strKey = CIniConfig::getKeyServerRobotUpdate();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}
//robot 1e
void CIniConfig::setValueServerRobotUpate(QString &strValue)
{
    QString strKey = CIniConfig::getKeyServerRobotUpdate();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

bool CIniConfig::getValueBigFrameDelay(int &nValue)
{
    QString strKey = CIniConfig::getKeyBigFrameDelay();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, nValue);
}

void CIniConfig::setValueBigFrameDelay(const int &nValue)
{
    QString strKey = CIniConfig::getKeyBigFrameDelay();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, nValue);
}

bool CIniConfig::getValueSmallFrameDelay(int &nValue)
{
    QString strKey = CIniConfig::getKeySmallFrameDelay();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, nValue);
}

void CIniConfig::setValueSmallFrameDelay(const int &nValue)
{
    QString strKey = CIniConfig::getKeySmallFrameDelay();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, nValue);
}

bool CIniConfig::getValueMLUserName(QString &strValue)
{
    const QString strKey = CIniConfig::getKeyMLUserName();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValueMLUserName(const QString &strValue)
{
    const QString strKey = CIniConfig::getKeyMLUserName();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

bool CIniConfig::getValueMLPassword(QString &strValue)
{
    QString strKey = CIniConfig::getKeyMLPassword();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValueMLPassword(const QString &strValue)
{
    const QString strKey = CIniConfig::getKeyMLPassword();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

bool CIniConfig::getValueMLUserType(int &nValue)
{
    QString strKey = CIniConfig::getKeyMLUserType();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, nValue);
}

void CIniConfig::setValueMLUserType(const int &nValue)
{
    const QString strKey = CIniConfig::getKeyMLUserType();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, nValue);
}

bool CIniConfig::getValueMLIsSave(bool &bSave)
{
    QString strKey = CIniConfig::getKeyMLIsSave();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, bSave);
}

void CIniConfig::setValueMLIsSave(const bool &bSave)
{
    const QString strKey = CIniConfig::getKeyMLIsSave();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, bSave);
}

bool CIniConfig::getValuePLCountryCode(QString &strValue)
{
    QString strKey = CIniConfig::getKeyPLCountryCode();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValuePLCountryCode(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyPLCountryCode();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

bool CIniConfig::getValuePLUserName(QString &strValue)
{
    QString strKey = CIniConfig::getKeyPLUserName();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValuePLUserName(const QString &strValue)
{
    const QString strKey = CIniConfig::getKeyPLUserName();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

bool CIniConfig::getValuePLPassword(QString &strValue)
{
    QString strKey = CIniConfig::getKeyPLPassword();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValuePLPassword(const QString &strValue)
{
    const QString strKey = CIniConfig::getKeyPLPassword();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

bool CIniConfig::getValuePLUserType(int &nValue)
{
    QString strKey = CIniConfig::getKeyPLUserType();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, nValue);
}

void CIniConfig::setValuePLUserType(const int &nValue)
{
    const QString strKey = CIniConfig::getKeyPLUserType();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, nValue);
}

bool CIniConfig::getValuePLIsSave(bool &bSave)
{
    QString strKey = CIniConfig::getKeyPLIsSave();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, bSave);
}

void CIniConfig::setValuePLIsSave(const bool &bSave)
{
    const QString strKey = CIniConfig::getKeyPLIsSave();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, bSave);
}

void CIniConfig::setPath(emFilePathType eType, const QString &strPath)
{
    const QString strKey = getKeyFilePath(eType);
    if (strKey.isEmpty())
    {
        return;
    }
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strPath);
}

bool CIniConfig::getPath(emFilePathType eType, QString &strPath)
{
    const QString strKey = getKeyFilePath(eType);
    if (strKey.isEmpty())
    {
        return false;
    }
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strPath);
}

/**************************************************************************
* 函数名: getUserLanguage
* 功能: 获取用户语言，首先从配置文件获取，没有从配置文件获取到时
*          以系统语言返回
* 参数:
* 返回值: QString: 返回的语言关键字
*             中文为：zh_CN
*             英文为：en
* 时间: 2016/07/17
* 作者: hwx
*/
QString CIniConfig::getValueLanguage()
{
    QString strKey = CIniConfig::getKeyLanguage();
    QString strLanguageKeyword;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strLanguageKeyword);

//使用系统语言由接口调用实现，接口不设置默认语言

//    // 如果配置文件没有记录语言信息，则使用系统语言
//    if (strLanguageKeyword.isEmpty())
//    {
//       strLanguageKeyword = QLocale::system().name();
//    }
    return strLanguageKeyword;
}

void CIniConfig::setValueLanguage(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyLanguage();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueUserID()
{
    QString strKey = CIniConfig::getKeyUserID();
    QString strUserIdKeyword;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strUserIdKeyword);

    return strUserIdKeyword;
}

void CIniConfig::setValueUserID(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyUserID();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueToken()
{
    QString strKey = CIniConfig::getKeyToken();
    QString strTokenKeyword;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strTokenKeyword);

    return strTokenKeyword;
}

void CIniConfig::setValueToken(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyToken();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getLoginType()
{
    QString strKey = CIniConfig::getKeyLoginType();
    QString strLoginType;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strLoginType);

    return strLoginType;
}

void CIniConfig::setLoginType(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyLoginType();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}




QString CIniConfig::getValueAlyOss()
{
    QString strKey = CIniConfig::getKeyNodeAlyOss();
    QString strAlyOss;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strAlyOss);
    return strAlyOss;
}

void CIniConfig::setValueAlyOss(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyNodeAlyOss();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueAccessKeyId()
{
    QString strKey = CIniConfig::getKeyAccessKeyId();
    QString strAccessKeyId;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strAccessKeyId);
    return strAccessKeyId;
}

void CIniConfig::setValueAccessKeyId(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyAccessKeyId();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueAccessKeySecret()
{
    QString strKey = CIniConfig::getKeyAccessKeySecret();
    QString strAccessKeySecret;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strAccessKeySecret);
    return strAccessKeySecret;
}

void CIniConfig::setValueAccessKeySecret(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyAccessKeySecret();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueEndpoint()
{
    QString strKey = CIniConfig::getKeyEndpoint();
    QString strEndpoint;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strEndpoint);
    return strEndpoint;
}

void CIniConfig::setValueEndpoint(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyEndpoint();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueBucketName()
{
    QString strKey = CIniConfig::getKeyBucketName();
    QString strBucketName;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strBucketName);
    return strBucketName;
}

void CIniConfig::setValueBucketName(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyBucketName();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueObjectName()
{
    QString strKey = CIniConfig::getKeyObjectName();
    QString strObjectName;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strObjectName);
    return strObjectName;
}

void CIniConfig::setValueObjectName(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyObjectName();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

QString CIniConfig::getValueSecurityToken()
{
    QString strKey = CIniConfig::getKeySecurityToken();
    QString strSecurityToken;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strSecurityToken);
    return strSecurityToken;
}

void CIniConfig::setValueSecurityToken(const QString &strValue)
{
    QString strKey = CIniConfig::getKeySecurityToken();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}


QString CIniConfig::getValueExpireTimestamp()
{
    QString strKey = CIniConfig::getKeyExpireTimestamp();
    QString strExpireTimestamp;
    CIniConfig::getValue(m_strConfigIniFilePath, strKey, strExpireTimestamp);
    return strExpireTimestamp;
}

void CIniConfig::setValueExpireTimestamp(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyExpireTimestamp();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}




bool CIniConfig::getValueRobotType(QString &strValue)
{
    QString strKey = CIniConfig::getKeyRobotType();
    return CIniConfig::getValue(m_strConfigIniFilePath, strKey, strValue);
}

void CIniConfig::setValueRobotType(const QString &strValue)
{
    QString strKey = CIniConfig::getKeyRobotType();
    CIniConfig::setValue(m_strConfigIniFilePath, strKey, strValue);
}

//bool CIniConfig::getValueIsLogEnable(bool &bEnable)
//{
//    QString strKey = CIniConfig::getKeyNodeConfig();
//    strKey = CIniConfig::getKey(strKey, LOG_ENABLE_KEYWORD);

//    CIniConfig::getValue(m_strConfigIniFilePath, strKey, bEnable);

//    return bEnable;
//}
