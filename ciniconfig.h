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


#ifndef CINICONFIG_H
#define CINICONFIG_H

#include <QString>
#include <QVariant>


enum emFilePathType
{
    eFilePathImportMusic = 0,  // 导入音乐文件路径
    eFilePathOpenProject, // 打开工程路径
};

extern const QString SETTING_SPLIT_CHART;


class  CIniConfig
{    
public:
    CIniConfig();
    ~CIniConfig();

public:
    static bool setValue(const QString& strFile, const QString& strKey, const QVariant &varValue);
    static bool getValue(const QString& strFile, const QString& strKey, int &nValue);
    static bool getValue(const QString& strFile, const QString& strKey, double &dValue);
    static bool getValue(const QString& strFile, const QString& strKey, QString &strValue);
    static bool getValue(const QString& strFile, const QString& strKey, bool &bValue);

    static QString getKey(const QString& strKeyPre, const QString& strKeySuffix);
    static QString getKey(const QString& strKeyPre, const QString& strKeyMid, const QString& strKeySuffix);

public:
    //for config.ini file
    //for config.ini file node of [Config]
    bool getValueActPath(QString &strValue);
    void setValueActPath(const QString &strValue);
    bool getValueServer(QString &strValue);
    void setValueServer(const QString &strValue);
    bool getValueServerRobotUpate(QString &strValue);
    void setValueServerRobotUpate(QString &strValue);


    bool getValueBigFrameDelay(int &nValue);
    void setValueBigFrameDelay(const int &nValue);
    bool getValueSmallFrameDelay(int &nValue);
    void setValueSmallFrameDelay(const int &nValue);


    //for config.ini file node of [UserInfo]
    //for mail login
    bool getValueMLUserName(QString &strValue);
    void setValueMLUserName(const QString &strValue);
    bool getValueMLPassword(QString &strValue);
    void setValueMLPassword(const QString &strValue);
    bool getValueMLUserType(int &nValue);
    void setValueMLUserType(const int &nValue);
    bool getValueMLIsSave(bool& bSave);
    void setValueMLIsSave(const bool& bSave);


    //for PhoneLogin login
    bool getValuePLCountryCode(QString &strValue);
    void setValuePLCountryCode(const QString &strValue);
    bool getValuePLUserName(QString &strValue);
    void setValuePLUserName(const QString &strValue);
    bool getValuePLPassword(QString &strValue);
    void setValuePLPassword(const QString &strValue);
    bool getValuePLUserType(int &nValue);
    void setValuePLUserType(const int &nValue);
    bool getValuePLIsSave(bool& bSave);
    void setValuePLIsSave(const bool& bSave);

    // 记录、读取历史文件路径
    void setPath(emFilePathType eType, const QString &strPath);
    bool getPath(emFilePathType eType, QString &strPath);



    ///////////////////////////////////////////setting
    //for config.ini file node of [LanguageSetting]
    QString getValueLanguage();
    void setValueLanguage(const QString &strValue);

    QString getValueUserID();
    void setValueUserID(const QString &strValue);

    QString getValueToken();
    void setValueToken(const QString &strValue);

    QString getLoginType();
    void setLoginType(const QString &strValue);

    QString getValueAlyOss();
    void setValueAlyOss(const QString &strValue);

    QString getValueAccessKeyId();
    void setValueAccessKeyId(const QString &strValue);

    QString getValueAccessKeySecret();
    void setValueAccessKeySecret(const QString &strValue);

    QString getValueEndpoint();
    void setValueEndpoint(const QString &strValue);

    QString getValueBucketName();
    void setValueBucketName(const QString &strValue);

    QString getValueObjectName();
    void setValueObjectName(const QString &strValue);

    QString getValueSecurityToken();
    void setValueSecurityToken(const QString &strValue);

    QString getValueExpireTimestamp();
    void setValueExpireTimestamp(const QString &strValue);

     //for config.ini file node of [RobotTypeSetting]
    bool getValueRobotType(QString &strValue);
    void setValueRobotType(const QString &strValue);


     QString getValueServerWebIp();
     void setValueServerWebIp(QString strIp);//robot update 1e

     QString getValueEnvironment();
     void setValueEnvironment(QString strEnvironment);

     QString getValueUsedFlag();
     void setValueUsedFlag(QString strUsedFlag);//robot update 1e

     QString  getWebVersion();
     void setWebVersion(QString strVersion);

     QString  getMainVersion();
     void setMainVersion(QString strVersion);

     QString  getMainVersionMd5();
     void setMainVersionMd5(QString strMd5);

     QString  getWebVersionMd5();
     void setWebVersionMd5(QString strMd5);

     QString  getIgnoreVersion();
     void setIgnoreVersion(QString strVersion);

     /**************************************************************************
     * 函数名: getMaxThreadCount
     * 功能:获取最大线程数量
     * 参数: [@in]
     * 参数: [@in]
     * 返回值:QString
     * 时间:2020/09/04
     * 作者: Joker
     */
     QString  getMaxThreadCount();

     /**************************************************************************
     * 函数名: setMaxThreadCount
     * 功能:设置最大线程数量
     * 参数: [@in]strMaxThreadCount
     * 参数: [@in]
     * 返回值:QString
     * 时间:2020/09/04
     * 作者: Joker
     */
     void setMaxThreadCount(QString strMaxThreadCount);


     /**************************************************************************
     * 函数名: getMaxBuff
     * 功能:获取最大传输buff
     * 参数: [@in]
     * 参数: [@in]
     * 返回值:QString
     * 时间:2020/09/04
     * 作者: Joker
     */
     QString  getMaxBuff();

     /**************************************************************************
     * 函数名: setMaxBuff
     * 功能:设置最大传输buff
     * 参数: [@in]strMaxThreadCount
     * 参数: [@in]
     * 返回值:QString
     * 时间:2020/09/04
     * 作者: Joker
     */
     void setMaxBuff(QString strMaxBuff);



//public:
//    //for log print
//    bool getValueIsLogEnable(bool &bEnable);

private:
    static QVariant getValue(const QString& strFile, const QString& strKey);


private:
    //for config.ini file
    //node of [Config]
    static QString getKeyNodeConfig();
    //node of [UserInfo]
    static QString getKeyNodeUserInfo();

    //
    static QString getKeyActPath();
    static QString getKeyServer();//1p
    static QString getKeyServerRobotUpdate();//robot update 1e

    static QString getKeyServerWebIp();//
    static QString getKeyEnvironment();//
    static QString getKeyUsedFlag();

    static QString getKeyBigFrameDelay();
    static QString getKeySmallFrameDelay();

    //
    static QString getKeyML();
    static QString getKeyPL();

    //mail login key
    static QString getKeyMLUserName();
    static QString getKeyMLPassword();
    static QString getKeyMLUserType();
    static QString getKeyMLIsSave();

    //phone login key
    static QString getKeyPLCountryCode();
    static QString getKeyPLUserName();
    static QString getKeyPLPassword();
    static QString getKeyPLUserType();
    static QString getKeyPLIsSave();

    // 获取文件路径
    static QString getKeyFilePath(emFilePathType eType);
    static QString getKeyMusicPath();
    static QString getKeyOpenProjPath();



    //node of [LanguageSetting]
    static QString getKeyNodeLanguageSetting();
    static QString getKeyLanguage();


    static QString getKeyNodeAlyOss();
    static QString getKeyAccessKeyId();
    static QString getKeyAccessKeySecret();
    static QString getKeyEndpoint();
    static QString getKeyBucketName();
    static QString getKeyObjectName();
    static QString getKeySecurityToken();
    static QString getKeyExpireTimestamp();
      //node of [UserInfo]

    static QString getKeyUserID();
    static QString getKeyToken();
    static QString getKeyLoginType();

     //for config.ini file node of [RobotTypeSetting]
    static QString getKeyNodeRobotTypeSetting();
    static QString getKeyRobotType();

    static QString getKeyNodeVersion();
    static QString getKeyWebVersion();
    static QString getKeyWebVersionMd5();
    static QString getKeyMainVersion();
    static QString getKeyMainVersionMd5();
    static QString getKeyIgnoreVersion();
    /**************************************************************************
    * 函数名: getKeyMaxThreadCount
    * 功能:获取最大线程数量key
    * 参数: [@in]
    * 参数: [@in]
    * 返回值:QString
    * 时间:2020/09/04
    * 作者: Joker
    */
    static QString getKeyMaxThreadCount();

    /**************************************************************************
    * 函数名: getKeyMaxBuff
    * 功能:获取最大传输buff
    * 参数: [@in]
    * 参数: [@in]
    * 返回值:QString
    * 时间:2020/09/04
    * 作者: Joker
    */
    static QString getKeyMaxBuff();



private:
    QString m_strConfigIniFilePath;

};

#endif // CINICONFIG_H
