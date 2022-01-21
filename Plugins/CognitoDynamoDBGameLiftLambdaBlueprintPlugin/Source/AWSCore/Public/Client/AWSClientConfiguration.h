/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, May 2019
 */

#pragma once

#include "CoreMinimal.h"

#if WITH_CORE

#include "aws/core/client/ClientConfiguration.h"

#endif

#include "AWSClientConfiguration.generated.h"

USTRUCT(BlueprintType)
struct FAWSClientConfiguration {
    GENERATED_USTRUCT_BODY()

    FAWSClientConfiguration() :
            scheme("https"),
            region("us-east-1"),
            useDualStack(false),
            maxConnections(25),
            requestTimeoutMs(3000),
            connectTimeoutMs(1000),
            proxyScheme("http"),
            proxyPort(0),
            verifySSL(true),
            followRedirects(true),
            disableExpectHeader(false),
            enableClockSkewAdjustment(true) {
    }

public:
    /**
     * Http scheme to use. E.g. Http or Https. Default HTTPS
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString scheme;

    /**
     * AWS Region to use in signing requests. Should be lower case. Default us-east-1
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString region;

    /**
     * Use dual stack endpoint in the endpoint calculation. It is your responsibility to verify that the service supports ipv6 in the region you select.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    bool useDualStack;

    /**
     * Max concurrent tcp connections for a single http client to use. Default 25.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    int32 maxConnections;

    /**
     * Socket read timeouts. Default 3000 ms. This should be more than adequate for most services. However, if you are transfering large amounts of data
     * or are worried about higher latencies, you should set to something that makes more sense for your use case.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    int32 requestTimeoutMs;

    /**
     * Socket connect timeout. Default 1000 ms. Unless you are very far away from your the data center you are talking to. 1000ms is more than sufficient.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    int32 connectTimeoutMs;

    /**
     * Override the http endpoint used to talk to a service.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString endpointOverride;

    /**
     * If you have users going through a proxy, set the proxy scheme here. Default HTTP
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString proxyScheme;

    /**
     * If you have users going through a proxy, set the host here.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString proxyHost;

    /**
     * If you have users going through a proxy, set the port here.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    uint8 proxyPort;

    /**
     * If you have users going through a proxy, set the username here.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString proxyUserName;

    /**
    * If you have users going through a proxy, set the password here.
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString proxyPassword;

    /**
     * If you need to test and want to get around TLS validation errors, do that here.
     * you probably shouldn't use this flag in a production scenario.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    bool verifySSL;

    /**
     * If you need to test and want to get around TLS validation errors, do that here.
     * you probably shouldn't use this flag in a production scenario.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString caPath;

    /**
     * If you need to test and want to get around TLS validation errors, do that here.
     * you probably shouldn't use this flag in a production scenario.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    FString caFile;

    /**
     * If set to true the http stack will follow 300 redirect codes.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    bool followRedirects;

    /**
     * Only works for Curl http client.
     * Curl will by default add "Expect: 100-Continue" header in a Http request so as to avoid sending http
     * payload to wire if server respond error immediately after receiving the header.
     * Set this option to true will tell Curl to send http request header and body together.
     * This can save one round-trip time and especially useful when the payload is small and network latency is more important.
     * But be careful when Http request has large payload such S3 PutObject. You don't want to spend long time sending a large payload just geting a error response for server.
     * The default value will be false.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    bool disableExpectHeader;

    /**
     * If set to true clock skew will be adjusted after each http attempt, default to true.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AWS Core")
    bool enableClockSkewAdjustment;

#if WITH_CORE
public:
    Aws::Client::ClientConfiguration toAWS() const {
        Aws::Client::ClientConfiguration awsClientConfiguration;
        awsClientConfiguration.scheme = Aws::Http::SchemeMapper::FromString(TCHAR_TO_UTF8(*this->scheme));
        awsClientConfiguration.region = TCHAR_TO_UTF8(*this->region);
        awsClientConfiguration.useDualStack = this->useDualStack;
        awsClientConfiguration.maxConnections = static_cast<unsigned int>(this->maxConnections);
        awsClientConfiguration.requestTimeoutMs = this->requestTimeoutMs;
        awsClientConfiguration.connectTimeoutMs = this->connectTimeoutMs;
        awsClientConfiguration.endpointOverride = TCHAR_TO_UTF8(*this->endpointOverride);
        awsClientConfiguration.proxyScheme = Aws::Http::SchemeMapper::FromString(
                TCHAR_TO_UTF8(*this->proxyScheme));
        awsClientConfiguration.proxyHost = TCHAR_TO_UTF8(*this->proxyHost);
        awsClientConfiguration.proxyPort = this->proxyPort;
        awsClientConfiguration.proxyUserName = TCHAR_TO_UTF8(*this->proxyUserName);
        awsClientConfiguration.proxyPassword = TCHAR_TO_UTF8(*this->proxyPassword);
        awsClientConfiguration.verifySSL = this->verifySSL;
        awsClientConfiguration.caPath = TCHAR_TO_UTF8(*this->caPath);
        awsClientConfiguration.caFile = TCHAR_TO_UTF8(*this->caFile);
        awsClientConfiguration.followRedirects = this->followRedirects;
        awsClientConfiguration.disableExpectHeader = this->disableExpectHeader;
        awsClientConfiguration.enableClockSkewAdjustment = this->enableClockSkewAdjustment;
        return awsClientConfiguration;
    };
#endif
};
