// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The POSQ developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "base58.h"
#include "chainparams.h"
#include "libzerocoin/Params.h"
#include "net.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"

/**
* Main network
*/

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
	// It'll only connect to one or two seed nodes because once it connects,
	// it'll get a pile of addresses with newer timestamps.
	// Seed nodes are given a random 'last seen time' of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int i = 0; i < count; i++) {
		struct in6_addr ip;
		memcpy(&ip, data[i].addr, sizeof(ip));
		CAddress addr(CService(ip, data[i].port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of

    (0, uint256("0x00000afed892c787c80d30221f112c4611013cf366b574cc9cf6149415a93957"))
    (150, uint256("0x0000007e1126eb31b9fb121ee9998a1978d35cad07e40d4f20e49d5d1273db1d"))
    (187, uint256("0x0000001d5a7da21869ae4e86751b8c0ab39510a5717b39dd7e170ef2ac2c6284"))
    (300, uint256("0x00000dc2f4498de11a9422abd4dd87b2b9d84e9135ab7982407178255a4e9a6c"))
    (600, uint256("0x2e95031c1e4eecd2cd3879b6572adb6ee6b480d429a6e13b1adbdc4539cb90df"))
    (1200, uint256("0xb81736ef9ffb8620b2f50088a08efff49496a1cf5b81f926a23c8c6c9eb53a3b"))
    (1800, uint256("0xb3b672c7845ddaf0ce2450d15dd15d5fe4951781ba242d00e6f778524835a54f"))
    (2400, uint256("0x28e65007cb1790fe87b7af7fa35b5728bfc88fbe6dc55df641fd11bf33a3dbdc"))
    (3000, uint256("0xa3fb3e642c502501f3f363da819fa4dc83b74893e0cce6802f4be2590d2f7b0e"))
    (11111, uint256("0x3be6f069ab16ddf8ab9cddee1c99e6c366243123d736a9ed5b245ef94bb380d9"))
    (24453, uint256("0x2dcbafa6b16282b79511d22a9377c2428ba79a67e5b06c9cdb2502cab2ecc15e"));

static const Checkpoints::CCheckpointData data = {
	&mapCheckpoints,
    1548444999, // * UNIX timestamp of last checkpoint block
	          // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the SetBestChain debug.log lines)
				2000        // * estimated number of transactions per day after checkpoint, was 2000
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
boost::assign::map_list_of
(0, uint256("0x5631b0ce092246abb7f7cbf0a6ee315bd7cf41092a714c7ece4c1aed15dd3995"));
static const Checkpoints::CCheckpointData dataTestnet = {
	&mapCheckpointsTestnet,
	1546206194,
	0,
	250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
boost::assign::map_list_of
(0, uint256("0x00000334ad7d19ac18efcc77b3bd54e62e16bb8ad96732cf8d01425557f8d78e"));
static const Checkpoints::CCheckpointData dataRegtest = {
	&mapCheckpointsRegtest,
	1546206278,
	0,
	100
};


libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
	assert(this);
	static CBigNum bnTrustedModulus(zerocoinModulus);
	static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

	return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
	CMainParams()
	{
		networkID = CBaseChainParams::MAIN;
		vReviveRewardAddress = "";   //This address will be depreicated when spork 18 is turned on and coins will be burned.
		vTreasuryRewardAddress = "Qdev17b5f11FoYwDvLKNDAjN3yBmRSLLzn";
		strNetworkID = "main";
		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/
		pchMessageStart[0] = 0x2c;
		pchMessageStart[1] = 0xad;
		pchMessageStart[2] = 0xe3;
		pchMessageStart[3] = 0x12;
		vAlertPubKey = ParseHex("0421303df706061f443fa153cf057b8c3bfd338f34a0661ce186001c6e7bf8fdbf71553d84d65f8463d74b73c0544ffffdad38658b25ca26bd22e5c9a27eee7583");
		nDefaultPort = 5510;
		bnProofOfWorkLimit = ~uint256(0) >> 1;
		nSubsidyHalvingInterval = 210000;
		nMaxReorganizationDepth = 100;
		nEnforceBlockUpgradeMajority = 750;
		nRejectBlockOutdatedMajority = 950;
		nToCheckBlockUpgradeMajority = 1000;
		nMinerThreads = 0;
		nTargetTimespan = 1 * 60;         // POSQ: 1 day
		nTargetSpacing = 1 * 60;          // POSQ: 1 minutes
		nMaturity = 25;                   // 25 Conf to mature coins
		nMasternodeCountDrift = 20;       //Was 20
		nMasternodeCollateralAmt = 5000; //masternode collateral 25K
		nMaxMoneyOut = 25000000 * COIN;  //25m coins minted

										  /** Height or Time Based Activations **/
		nLastPOWBlock = 400;
		nModifierUpdateBlock = 1; //Was 999999999
		nZerocoinStartHeight = 401;
		nAccumulatorStartHeight = 1;
		nZerocoinStartTime = 1534438799;
		nBlockEnforceSerialRange = 1;       //Enforce serial range starting this block
		nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
		nBlockFirstFraudulent = ~1;         //First block that bad serials emerged
		nBlockLastGoodCheckpoint = ~1;      //Last valid accumulator checkpoint

		const char* pszTimestamp = "12/30/2018 Craig Wright Denied USD 1 Billion Lawsuit Dismissal";
		CMutableTransaction txNew;
		txNew.vin.resize(1);
		txNew.vout.resize(1);
		txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		txNew.vout[0].nValue = 50 * COIN;
		txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1546206065;
		genesis.nBits = 504365040;
		genesis.nNonce = 514578;


		nEnforceNewSporkKey = 1546300800; //!> Sporks signed after (GMT): Tuesday, Jan 1, 2018 12:00:00 AM GMT must use the new spork key
        	nRejectOldSporkKey = 1548979200;  //!> Fully reject old spork key after (GMT): Friday, Feb 1, 2018 12:00:00 AM


		hashGenesisBlock = genesis.GetHash();

		//printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
		//printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());

		assert(hashGenesisBlock == uint256("0x00000afed892c787c80d30221f112c4611013cf366b574cc9cf6149415a93957"));
		assert(genesis.hashMerkleRoot == uint256("0x5631b0ce092246abb7f7cbf0a6ee315bd7cf41092a714c7ece4c1aed15dd3995"));

		//Teams Seeder
		vSeeds.push_back(CDNSSeedData("seed.posq.space", "seed.posq.space"));
		//Seeds	Community Nodes
		vSeeds.push_back(CDNSSeedData("posq.seeds.mn.zone", "posq.seeds.mn.zone"));
		vSeeds.push_back(CDNSSeedData("posq.mnseeds.com", "posq.mnseeds.com"));
		vSeeds.push_back(CDNSSeedData("207.246.112.156", "207.246.112.156"));


		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 58); //Q
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
		// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xbc).convert_to_container<std::vector<unsigned char> >();

		convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

		fRequireRPCPassword = true;
		fMiningRequiresPeers = false;
		fAllowMinDifficultyBlocks = false;
		fDefaultConsistencyChecks = false;
		fRequireStandard = true;
		fMineBlocksOnDemand = false;
		fSkipProofOfWorkCheck = false;
		fTestnetToBeDeprecatedFieldRPC = false;
		fHeadersFirstSyncingActive = false;

		nPoolMaxTransactions = 3;

        strSporkKey = "034eea79b60108d63a9123cab5b708dacdc3ba2cb643466e8543a2e50f271c1ada";
        strSporkKeyOld = "030262a2a0679d01ab026d375c42b0a4122477123631b870e09665526c322c8899";

		strObfuscationPoolDummyAddress = "QfKpz2Vrh4XbfJNahntTJSDhSBmCEvUVZ3";
		nStartMasternodePayments = 1534438799;

		/** Zerocoin */
        zerocoinModulus = "c247e97631b8249acb00b7f7f7c9cb57825d2a07c6e20d84c4f3c02a0e2e38b703d24b2204d0363bc2782b1e87e40d90a3"
            "c94f93abb1dc4efa8f3ab3d8ca5b837fbcbe5b465a93543a1ee51ca8bafcccdc8a0f3fd74cee7585d5696040ceac58796ff1e928ce9eb968"
            "571e02649c28b3a5ba94a5d2dd74dc1ca85aab0573c4b435f0327409c91c7819db1799b93d514576dfcabbcea29d4bb27016e554bea03586"
            "d3f4264f34c6baf21865cf1564c85c8f7a7cb83d0b94db81367e7ef83310a70ba80c99b80702721084a7c5eea599f640ce8e6ec44db2c604"
            "0b6f8a7449b345ffc730415c64c628c078ef701e1559bc6b965ef2eb1deecc74611fb116fee980c9cea978d8f1f37d66d05ad56f52f52099"
            "5b7f4e436c365f8f7e44eaf91447f48d8fc211f8e874fef249076425aa9cfae10fc3a347432028ff9ab29c3a6346ade6fe21f36254b9dc26"
            "09eb03ddf7c9a9da3b44bbe48ca7fe59daac240b384da5b29fb5c522a9c0600f11eb7a45796a6f30c4819b6573ea38e735d9b7c9e95c49";
		nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
		nMinZerocoinMintFee = 1 * ZCENT;      //high fee required for zerocoin mints
		nMintRequiredConfirmations = 20;      //the maximum amount of confirmations until accumulated in 19
		nRequiredAccumulation = 1;
		nDefaultSecurityLevel = 100;   //full security level for accumulators
		nZerocoinHeaderVersion = 4;    //Block headers must be this version once zerocoin is active
		nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return data;
	}
};

std::string CChainParams::GetTreasuryRewardAddressAtHeight(int nHeight) const
{
	return vTreasuryRewardAddress;
}

CScript CChainParams::GetTreasuryRewardScriptAtHeight(int nHeight) const
{
	CBitcoinAddress address(GetTreasuryRewardAddressAtHeight(nHeight).c_str());
	assert(address.IsValid());
	CScript script = GetScriptForDestination(address.Get());
	return script;
}

std::string CChainParams::GetReviveRewardAddressAtHeight(int nHeight) const
{
	return vReviveRewardAddress;
}
CScript CChainParams::GetReviveRewardScriptAtHeight(int nHeight) const
{
	CBitcoinAddress address(GetReviveRewardAddressAtHeight(nHeight).c_str());
	assert(address.IsValid());
	CScript script = GetScriptForDestination(address.Get());
	return script;
}


static CMainParams mainParams;

class CTestNetParams : public CMainParams
{
public:
	CTestNetParams()
	{
		networkID = CBaseChainParams::TESTNET;
		strNetworkID = "test";
		pchMessageStart[0] = 0x2a;
		pchMessageStart[1] = 0x3c;
		pchMessageStart[2] = 0xb5;
		pchMessageStart[3] = 0xe1;
		vAlertPubKey = ParseHex("0470a2eb34175354bd51b62d7080951ab15f360a15a53df8deec17b25bf076e30ddfc924d39c4d0f58ecba3e8676d818bfc6f491c651cc829849a8025d4f2ac9e2");
		nDefaultPort = 15510;
		nEnforceBlockUpgradeMajority = 750;
		nRejectBlockOutdatedMajority = 950;
		nToCheckBlockUpgradeMajority = 1000;
		nMinerThreads = 0;
		nTargetTimespan = 1 * 60; // POSQ: 1 day
		nTargetSpacing = 1 * 60;  // POSQ: 1 minute
		nLastPOWBlock = 400;
		nMaturity = 10;
		nMasternodeCountDrift = 4;
		nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
		nMaxMoneyOut = 100000000 * COIN;
		nZerocoinStartHeight = 201;
		nZerocoinStartTime = 1534438799;
		nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
		nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
		nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
		nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nTime = 1546206194;
		genesis.nNonce = 773271;



		hashGenesisBlock = genesis.GetHash();
		//printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
		assert(hashGenesisBlock == uint256("0x0000073f1de9d1268731bff93d98a357572d1665aed31e5893961dc3d96a8032"));
		assert(genesis.hashMerkleRoot == uint256("0x5631b0ce092246abb7f7cbf0a6ee315bd7cf41092a714c7ece4c1aed15dd3995"));

        	vFixedSeeds.clear();
        	vSeeds.clear();
		//Testnet Community Nodes
		vSeeds.push_back(CDNSSeedData("207.246.95.9", "207.246.95.9"));
		vSeeds.push_back(CDNSSeedData("140.82.61.65", "140.82.61.65"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet posq addresses start with 'x' or 'y'
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet posq script addresses start with '8' or '9'
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
																			 // Testnet posq BIP32 pubkeys start with 'DRKV'
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
		// Testnet posq BIP32 prvkeys start with 'DRKP'
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
		// Testnet posq BIP44 coin type is '1' (All coin's testnet default)
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

		convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

		fRequireRPCPassword = true;
		fMiningRequiresPeers = true;
		fAllowMinDifficultyBlocks = true;
		fDefaultConsistencyChecks = false;
		fRequireStandard = false;
		fMineBlocksOnDemand = false;
		fTestnetToBeDeprecatedFieldRPC = true;

		nPoolMaxTransactions = 2;
		strSporkKey = "034fa3a5a557ca5a0f86b676c55e855195e21ebf4e44b3c11a2ebce8600171346d";
		strObfuscationPoolDummyAddress = "XCNAsFGy8k7amqRG26ikKyfVDwK8585Z6b";
		nStartMasternodePayments = 1534438799;
		nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
									   // here because we only have a 8 block finalization window on testnet
	}
	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataTestnet;
	}
};
static CTestNetParams testNetParams;

class CRegTestParams : public CTestNetParams
{
public:
	CRegTestParams()
	{
		networkID = CBaseChainParams::REGTEST;
		strNetworkID = "regtest";
		strNetworkID = "regtest";
		pchMessageStart[0] = 0x12;
		pchMessageStart[1] = 0xc4;
		pchMessageStart[2] = 0xb3;
		pchMessageStart[3] = 0x15;
		nSubsidyHalvingInterval = 150;
		nEnforceBlockUpgradeMajority = 750;
		nRejectBlockOutdatedMajority = 950;
		nToCheckBlockUpgradeMajority = 1000;
		nMinerThreads = 1;
		nTargetTimespan = 1 * 60; // POSQ: 1 day
		nTargetSpacing = 1 * 60;        // POSQ: 1 minutes
		bnProofOfWorkLimit = ~uint256(0) >> 1;
		genesis.nTime = 1546206278;
		genesis.nBits = 504365040;
		genesis.nNonce = 348846;


		hashGenesisBlock = genesis.GetHash();
		nDefaultPort = 15110;
		//printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
		//printf("%s\n", hashGenesisBlock.ToString().c_str());
		assert(hashGenesisBlock == uint256("0x00000334ad7d19ac18efcc77b3bd54e62e16bb8ad96732cf8d01425557f8d78e"));
		assert(genesis.hashMerkleRoot == uint256("0x5631b0ce092246abb7f7cbf0a6ee315bd7cf41092a714c7ece4c1aed15dd3995"));

		vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

		fRequireRPCPassword = false;
		fMiningRequiresPeers = false;
		fAllowMinDifficultyBlocks = true;
		fDefaultConsistencyChecks = true;
		fRequireStandard = false;
		fMineBlocksOnDemand = true;
		fTestnetToBeDeprecatedFieldRPC = false;
	}
	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataRegtest;
	}
};
static CRegTestParams regTestParams;

class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
	CUnitTestParams()
	{
		networkID = CBaseChainParams::UNITTEST;
		strNetworkID = "unittest";
		nDefaultPort = 18334;
		vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

		fRequireRPCPassword = false;
		fMiningRequiresPeers = false;
		fDefaultConsistencyChecks = true;
		fAllowMinDifficultyBlocks = false;
		fMineBlocksOnDemand = true;
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		// UnitTest share the same checkpoints as MAIN
		return data;
	}

	//! Published setters to allow changing values in unit test cases
	virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
	virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
	virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
	virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
	virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
	virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
	virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
	assert(pCurrentParams);
	return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
	switch (network) {
	case CBaseChainParams::MAIN:
		return mainParams;
	case CBaseChainParams::TESTNET:
		return testNetParams;
	case CBaseChainParams::REGTEST:
		return regTestParams;
	default:
		assert(false && "Unimplemented network");
		return mainParams;
	}
}

void SelectParams(CBaseChainParams::Network network)
{
	SelectBaseParams(network);
	pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
	CBaseChainParams::Network network = NetworkIdFromCommandLine();
	if (network == CBaseChainParams::MAX_NETWORK_TYPES)
		return false;

	SelectParams(network);
	return true;
}
