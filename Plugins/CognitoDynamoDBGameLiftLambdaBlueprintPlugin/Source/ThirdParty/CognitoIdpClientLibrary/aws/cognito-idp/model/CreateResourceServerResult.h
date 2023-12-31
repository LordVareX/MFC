﻿/*
* Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#pragma once
#include <aws/cognito-idp/CognitoIdentityProvider_EXPORTS.h>
#include <aws/cognito-idp/model/ResourceServerType.h>
#include <utility>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace CognitoIdentityProvider
{
namespace Model
{
  class AWS_COGNITOIDENTITYPROVIDER_API CreateResourceServerResult
  {
  public:
    CreateResourceServerResult();
    CreateResourceServerResult(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    CreateResourceServerResult& operator=(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);


    /**
     * <p>The newly created resource server.</p>
     */
    inline const ResourceServerType& GetResourceServer() const{ return m_resourceServer; }

    /**
     * <p>The newly created resource server.</p>
     */
    inline void SetResourceServer(const ResourceServerType& value) { m_resourceServer = value; }

    /**
     * <p>The newly created resource server.</p>
     */
    inline void SetResourceServer(ResourceServerType&& value) { m_resourceServer = std::move(value); }

    /**
     * <p>The newly created resource server.</p>
     */
    inline CreateResourceServerResult& WithResourceServer(const ResourceServerType& value) { SetResourceServer(value); return *this;}

    /**
     * <p>The newly created resource server.</p>
     */
    inline CreateResourceServerResult& WithResourceServer(ResourceServerType&& value) { SetResourceServer(std::move(value)); return *this;}

  private:

    ResourceServerType m_resourceServer;
  };

} // namespace Model
} // namespace CognitoIdentityProvider
} // namespace Aws
