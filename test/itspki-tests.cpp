#include "gtest/gtest.h"
#include "itspki-cmd-args.hh"
#include "itspki-common.hh"
#include "its/itspki-internal-data.hh"
#include "its/itspki-session.hh"

#define ITS_PKI_DEBUG 1

const char *profile = "TestDemoProfile";
const char *its_canonical_id_header = "TEST-ITSPKI";
std::string its_tkey_pubkey_id = "51AC321296526271";
const char *its_canonical_id = "TEST-ITSPKI-XXXXXX-51AC321296526271";
const char *its_tkey =  "MHcCAQEEIGjdbEK4O35mcWTsC7LhY/YoZdZINpu16Zm3JQQVZb7CoAoGCCqGSM49AwEHoUQDQgAE5vxO9sNaJqWdkBj19TWHY0yWwRHvPxiWTxjQEEIRS07b8uA3mCmkWg8blGwa2uItzd5Djdgpxjwv3TWVaedxoA==";
const char *its_tpubkey = "MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE5vxO9sNaJqWdkBj19TWHY0yWwRHvPxiWTxjQEEIRS07b8uA3mCmkWg8blGwa2uItzd5Djdgpxjwv3TWVaedxoA==";
const char *its_register_resp_id_hex = "3930363932";
const char *ec_psidssp_seq = "623:01C0";
const char *its_ec_ekey = "MHcCAQEEIGjdbEK4O35mcWTsC7LhY/YoZdZINpu16Zm3JQQVZb7CoAoGCCqGSM49AwEHoUQDQgAE5vxO9sNaJqWdkBj19TWHY0yWwRHvPxiWTxjQEEIRS07b8uA3mCmkWg8blGwa2uItzd5Djdgpxjwv3TWVaedxoA==";
const char *its_ec_vkey = "MHcCAQEEIIQ80EJBAu3M2YIwV6bBIJXWAVyauRZ4/OJxCr5JUNzsoAoGCCqGSM49AwEHoUQDQgAEsddOL9IUVMNmbKJdDXwJdGCs3VIjMyITq6NnM3ov6LqNzP16kvgLJC5oOwVNEy9Hpdmng5jnlKNrbdeNxcXsTA==";
const char *its_ec_cert = "gAMAgGzCAjtRFQA+EYEtQkVOQ0gtSVRTUEtJLVVUT1BJQS0yMDE5MDgyMS01MUFDMzIxMjk2NTI2MjcxAAAAAAAddbU/hGaoAQGAAgJvgQMCAcAAgIQ53B6Qrg3qP0rzmzdoKZ3XvJQWAD6j1s3V2YUTh7/jnoeKB5WWbRvsfchhGXWUJfWFZM7Yd1KdmRKghNGhEDX+gICEsddOL9IUVMNmbKJdDXwJdGCs3VIjMyITq6NnM3ov6LqNzP16kvgLJC5oOwVNEy9Hpdmng5jnlKNrbdeNxcXsTIGAR2DMKQiGp5ft2f4cp5wy1j75pwFfw5FW8WPKnlKogG8f+vslg5al2DulM2sViHqcBs68YxCLsXdakAicAXJ5Qg==";

const char *ea_cert =     "gAMAgEJI3Vtd8DQ7GYEPVVRPUElBX1RFU1RfRUExAAAAAAAcaAP1hgAFAQGAAgJvgQMCAQ4BAaCAAQiAASSCCAMB//wD/wADgAElggoEAf///wT/AAAAgAGJggYCAeAC/x+AAYqCBgIBwAL/P4ABi4IOBgGUAAD/+Ab/AAAAAAeAAYyCCgQB///gBP8AAB+AAY2CBAEAAf+AAgJvggYCAcAC/z8BAsAAgIM1LJ4tKr0xTF+JvyQ2VveGsGC9Y5sk7nVWAUV4WnOqvYCBg4FkhxryzyZC0LhFAPQLS0HTL/hkr9AQpFpum9Ijnh7vgmGAEGN8z7U89CM55+ZmAV1Da1/mTxTATVG0otBxh3eCq+r6RN6vs4gHXCPGNot6jdn5GxhH+hgt38bOyBThgikQO21t31n1yr9Lo6U8EMvCpcrZf6ERUIIPqrY/CfpWlVvs";
const char *ea_eprvkey =  "MHcCAQEEIAbrDYMUrcTDVkqOch3xNy/1S1xyXQni41Py0KRgA6uGoAoGCCqGSM49AwEHoUQDQgAENSyeLSq9MUxfib8kNlb3hrBgvWObJO51VgFFeFpzqr2oe00luNdm9kxYwnwHhxvoMW3FkVMDk2/UiX95bKkFHw==";
const char *ea_vprvkey =  "MHgCAQEEIIGuWY7xhEpha3oiP/Nk7VhyacnIE+9rwPETAV6pWdMAoAsGCSskAwMCCAEBB6FEA0IABIFkhxryzyZC0LhFAPQLS0HTL/hkr9AQpFpum9Ijnh7vms1jvDQJscdeik2lGQ2Fad8qPRDoUlOzJpzNjp4NmWk=";

const char *at_psidssp_seq = "36:010000";
const char *aa_cert = "gAMAgEJI3Vtd8DQ7GYEPVVRPUElBX1RFU1RfQUExAAAAAAAcaAP1hgAFAQGAAgJvgQMCATIBAaCAAQeAASSCCAMB//wD/wADgAElggoEAf///wT/AAAAgAGJggYCAeAC/x+AAYqCBgIBwAL/P4ABi4IOBgGUAAD/+Ab/AAAAAAeAAYyCCgQB///gBP8AAB+AAY2CBAEAAf8BAsAAgIJMVUp2x5WNacXWRpvKchhjsd1yP92YgzWDn12PETgY7YCAglNasR1KApOsr5xX3kyeek2eDbKzzd7M5+SxcSn/I/5FgmGAV9vbLo+GyAgKndOwwOWAlGWUxtqzAJe7gLTLheTaqdR7puulu+wB6/L7hvUJPAnDFDfL/RYlTGpE0lZN3rzqQBTUN3fe1jlB7AvglB4Fwun16QJ4X/I8+7jcFRiJWBQM";
const char *aa_eprvkey = "MHcCAQEEIG5z9nMs23NGMQ5+yaY4DBgcCQOY7k792yG0KT5KtjmCoAoGCCqGSM49AwEHoUQDQgAETFVKdseVjWnF1kabynIYY7Hdcj/dmIM1g59djxE4GO360nczBJMwFcZz7EToYP1/HL+mqEYVSGZfTQigFtr4Kg=="; 
const char *aa_vprvkey = "MHcCAQEEINtyHAna5goGgh6zfaIftVDSpQLLes2hqC0SLPpef9uuoAoGCCqGSM49AwEHoUQDQgAEU1qxHUoCk6yvnFfeTJ56TZ4NsrPN3szn5LFxKf8j/kXd51rBO8iYsAxMO0siEaIJPejNv+nyIrH3F5/vNiG6HA=="; 

const char *blob_its_register_response = "7B226964223A223930363932222C2263616E6F6E6963616C4964223A2242454E43482D495453504B492D55544F5049412D32303139303832312D35314143333231323936353236323731222C22746563686E6963616C5075626C69634B6579223A224D466B77457759484B6F5A497A6A3043415159494B6F5A497A6A304441516344516741453576784F39734E614A7157646B426A313954574859307957775248765078695754786A514545495253303762387541336D436D6B576738626C477761327549747A6435446A646770786A777633545756616564786F413D3D222C22737461747573223A22414354495641544544222C2270726F66696C65223A225465737444656D6F50726F66696C65222C2274616773223A5B5D2C2265634E756D626572223A307D";

const char *blob_ec_inner_request = "0023544553542D495453504B492D5858585858582D3531414333323132393635323632373101808084B1D74E2FD21454C3666CA25D0D7C097460ACDD5223332213ABA367337A2FE8BA8DCCFD7A92F80B242E683B054D132F47A5D9A78398E794A36B6DD78DC5C5EC4C008084E6FC4EF6C35A26A59D9018F5F53587634C96C111EF3F18964F18D01042114B4EDBF2E0379829A45A0F1B946C1ADAE22DCDDE438DD829C63C2FDD359569E771A00401018002026F81030201C0";

const char *blob_ec_enrollment_request = "03820101826CC2023B5115003E80835053DA3512F13D654F2F6F6200D9D3742ECD950F232CE1C88CAB60A655CDC4EF6FD766621A1F7C89E70A3676DB4197FC84B7E6B08A0D03EE1E595C3704F2B95580BCB7E4DFCB9BA1ADC484AE3D820179EA19B4368C2D70D924430C336B0A63DFB45C73D735FF75942CC979E78D362FBC612510F49A46D3C680757C2AA800FC6ED5DAA126880948F66DA79F157E03652BA2CA7BC737494811A68766D89DFA4EAA2FAF2F0FBC38FC5CF5D6A4BC64940F85D4B2C82837997ACDC14BAAE5C5B06611AC11375863962D1E051BCB7ED0BEF5950C173F8C022353EEDD6B0D44327387A1B4D1392A0AD7A1C642BCAAE73C70FDBCB458A939FFCAB8E2A7702FD3486D87D3962091FF8042415C8EA54948072F00341130064A0B372C5DC1B360D150D4C518C123FA3D895B4200377C621E14C812A2E1CB12CDD4B9C898B14C6FB1D93EAD5B7E5B8272DB91066D44E9453613DB5D3AA54D54F40316BEF16F7E8909786B10C1AF9E6EA5763FE0517345B0305A95E2829E8CB50FCBBAD4B01F446853B36F5996B51BE258F9C5C912CE7A4B1C85162F9A2BC6F1DC51CA38981CB0CDFAEF230A212EED948BDB8BFA1339B3FF5965B4E6EF181DE653581A12589DEF60E69908EC66AC045D761035349C50";

const char *blob_ec_enrollment_response = "0382010180013132D773EEEDF6809A9505B75196525ED4240C8782019F656A0473741C85143760D31D9ECAE50BB73208F2F157BBB872ADCEC24228C1FA74FDA405D43B0C822C0AA55B360731820B11C6E5A621AF00EA5726E965C083D81364086D95D644064FA281F558F4A0FD3FA027932F32EB87117C2BDDA8D30E2CAE00912AACEDC1CBF5C5DDE8B766C1789AFD7989739FD86FFA3EDDFC5353B6935EE5C8EFAE24CE6B0B15C463A422682735AD50C4B9F5C1CA9B8242BCA4433E6E35DBB4998E2BD6E16A7999CC43DBA95A86C82945A07C40284CB829AACCA1142FF92967F47CD837661BCE43A27AC3507EFF4D2564AAD6D91AA03691DCFB4DFC30A9599179399BC08257295D05A57F9F607F6D9051455FEA9D5EABBE429EFCE50B8D44EAA20444651FC3EF12BACA5C5D1865592153B718ECEF4C5C6877576B5E7CCDF04EE84F6AB6EFA0408B9CFF2AA059631963834D08BD3325D938DC435EFFE3C576DF25DC931D21D0D7C1616F9F2415A51EDFD2326C863367305A023C1D1E5AD5DE4E2DED9C2FD03D06D612CBF7DA0CFFB281D24AD0A7901F458DCC2F7E0E56E984860FFD982382DA758AA6699D3F7C297908D63BF545498BD75D286A0A9E";

void defaultCmdArgs(ItsPkiCmdArguments &cmd_args)
{
	// ITS Regiser
	cmd_args.its_canonical_id = its_canonical_id; 
	cmd_args.its_name_header = std::string(its_canonical_id_header);
	cmd_args.profile = std::string(profile);
	cmd_args.its_tkey_b64 = std::string(its_tkey);
	cmd_args.ec_psidssp_seq = std::string(ec_psidssp_seq);

	cmd_args.its_ec_vkey_b64 = std::string(its_ec_vkey);
	cmd_args.its_ec_cert_b64 = std::string(its_ec_cert);
	cmd_args.its_ec_ekey_b64 = std::string(its_ec_ekey);
	cmd_args.eacert_b64 = std::string(ea_cert);
	cmd_args.its_ec_ekey_enable = true;
	
	cmd_args.aacert_b64 = std::string(aa_cert);
	cmd_args.at_psidssp_seq = std::string(at_psidssp_seq);
	cmd_args.its_at_ekey_enable = true;
}

TEST(its_register_request, add)
{
// {
//  "canonicalId":"BENCH-ITSPKI-UTOPIA-20190821-51AC321296526271",
//  "profile":"TestDemoProfile",
//  "technicalPublicKey":"MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE5vxO9sNaJqWdkBj19TWHY0yWwRHvPxiWTxjQEEIRS07b8uA3mCmkWg8blGwa2uItzd5Djdgpxjwv3TWVaedxoA==",
//  "status":"ACTIVATED"
// }
	ItsPkiCmdArguments cmd_args;
	defaultCmdArgs(cmd_args);

	ItsPkiInternalData idata;
	
	ASSERT_TRUE(ParseItsRegisterCmdArguments(cmd_args, idata));
	ItsPkiSession session(idata);
	
	OCTETSTRING request;
        ASSERT_TRUE(session.ItsRegisterRequest_Create(idata, request));
	ASSERT_TRUE(session.sessionGetCanonicalId(idata) == its_canonical_id);
	std::string request_json = std::string((const char *)((const unsigned char *)request), request.lengthof());
	
	std::string json_canonical_id;
	ASSERT_TRUE(json_get_tag_value(request_json,"canonicalId", json_canonical_id));
	ASSERT_STREQ(json_canonical_id.c_str(),its_canonical_id);

	std::string json_tpubkey;
	ASSERT_TRUE(json_get_tag_value(request_json,"technicalPublicKey", json_tpubkey));
	ASSERT_STREQ(json_tpubkey.c_str(), its_tpubkey);

	std::string json_status;
	ASSERT_TRUE(json_get_tag_value(request_json,"status", json_status));
	ASSERT_STREQ(json_status.c_str(), "ACTIVATED");
}


TEST(its_register_response, add)
{
// {
//  "id":"90692",
//  "canonicalId":"BENCH-ITSPKI-UTOPIA-20190821-51AC321296526271",
//  "technicalPublicKey":"MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE5vxO9sNaJqWdkBj19TWHY0yWwRHvPxiWTxjQEEIRS07b8uA3mCmkWg8blGwa2uItzd5Djdgpxjwv3TWVaedxoA==",
//  "status":"ACTIVATED",
//  "profile":"TestDemoProfile",
//  "tags":[],
//  "ecNumber":0
// }
	ItsPkiCmdArguments cmd_args;
	defaultCmdArgs(cmd_args);

	ItsPkiInternalData idata;
	
	ASSERT_TRUE(ParseItsRegisterCmdArguments(cmd_args, idata));
	ItsPkiSession session(idata);
	
	OCTETSTRING response = str2oct(blob_its_register_response);
	OCTETSTRING ret_its_id;
        ASSERT_TRUE(session.ItsRegisterResponse_Parse(response, ret_its_id));
	ASSERT_EQ(ret_its_id, str2oct(its_register_resp_id_hex));
}


// PKIITS_CMDARG_ITS_TKEY="MHcCAQEEIGjdbEK4O35mcWTsC7LhY/YoZdZINpu16Zm3JQQVZb7CoAoGCCqGSM49AwEHoUQDQgAE5vxO9sNaJqWdkBj19TWHY0yWwRHvPxiWTxjQEEIRS07b8uA3mCmkWg8blGwa2uItzd5Djdgpxjwv3TWVaedxoA=="
// PKIITS_CMDARG_EA_CERT="gAMAgEJI3Vtd8DQ7GYEPVVRPUElBX1RFU1RfRUExAAAAAAAcaAP1hgAFAQGAAgJvgQMCAQ4BAaCAAQiAASSCCAMB//wD/wADgAElggoEAf///wT/AAAAgAGJggYCAeAC/x+AAYqCBgIBwAL/P4ABi4IOBgGUAAD/+Ab/AAAAAAeAAYyCCgQB///gBP8AAB+AAY2CBAEAAf+AAgJvggYCAcAC/z8BAsAAgIM1LJ4tKr0xTF+JvyQ2VveGsGC9Y5sk7nVWAUV4WnOqvYCBg4FkhxryzyZC0LhFAPQLS0HTL/hkr9AQpFpum9Ijnh7vgmGAEGN8z7U89CM55+ZmAV1Da1/mTxTATVG0otBxh3eCq+r6RN6vs4gHXCPGNot6jdn5GxhH+hgt38bOyBThgikQO21t31n1yr9Lo6U8EMvCpcrZf6ERUIIPqrY/CfpWlVvs"
// PKIITS_CMDARG_ITS_EC_EKEY_ENABLE=true
// PKIITS_CMDARG_ITS_CANONICAL_ID="BENCH-ITSPKI-UTOPIA-20190821-51AC321296526271"
// PKIITS_CMDARG_EC_PSIDSSP_SEQ="623:01C0"
TEST(its_enrollment_ec_request, add)
{
	ItsPkiCmdArguments cmd_args;
	defaultCmdArgs(cmd_args);

	ItsPkiInternalData idata;
	
	ASSERT_TRUE(ParseEcEnrollmentCmdArguments(cmd_args, idata));
	ItsPkiSession session(idata);

        EtsiTs102941TypesEnrolment::InnerEcRequest ec_inner_request;
	ASSERT_TRUE(session.EcEnrollmentRequest_InnerEcRequest(idata, ec_inner_request));
	
	OCTETSTRING ec_inner_request_encoded;
	ASSERT_TRUE(encInnerEcRequest(ec_inner_request, ec_inner_request_encoded));
	ASSERT_EQ(ec_inner_request_encoded, str2oct(blob_ec_inner_request));

	OCTETSTRING ec_enrollment_request;
        ASSERT_TRUE(session.EcEnrollmentRequest_Create(idata, ec_enrollment_request));

	void *prvkey = ECKey_ReadPrivateKeyB64(ea_eprvkey);
	ASSERT_TRUE(session.EcEnrollmentRequest_Parse(ec_enrollment_request, prvkey, ec_inner_request));
	
	ASSERT_TRUE(encInnerEcRequest(ec_inner_request, ec_inner_request_encoded));
	ASSERT_EQ(its_canonical_id, ec_inner_request.itsId());
	ASSERT_EQ(ec_inner_request_encoded, str2oct(blob_ec_inner_request));

	ec_enrollment_request = str2oct(blob_ec_enrollment_request);
	ASSERT_TRUE(session.EcEnrollmentRequest_Parse(ec_enrollment_request, prvkey, ec_inner_request));
}

// PKIITS_CMDARG_EA_CERT="gAMAgEJI3Vtd8DQ7GYEPVVRPUElBX1RFU1RfRUExAAAAAAAcaAP1hgAFAQGAAgJvgQMCAQ4BAaCAAQiAASSCCAMB//wD/wADgAElggoEAf///wT/AAAAgAGJggYCAeAC/x+AAYqCBgIBwAL/P4ABi4IOBgGUAAD/+Ab/AAAAAAeAAYyCCgQB///gBP8AAB+AAY2CBAEAAf+AAgJvggYCAcAC/z8BAsAAgIM1LJ4tKr0xTF+JvyQ2VveGsGC9Y5sk7nVWAUV4WnOqvYCBg4FkhxryzyZC0LhFAPQLS0HTL/hkr9AQpFpum9Ijnh7vgmGAEGN8z7U89CM55+ZmAV1Da1/mTxTATVG0otBxh3eCq+r6RN6vs4gHXCPGNot6jdn5GxhH+hgt38bOyBThgikQO21t31n1yr9Lo6U8EMvCpcrZf6ERUIIPqrY/CfpWlVvs"
// PKIITS_CMDARG_AA_CERT="gAMAgEJI3Vtd8DQ7GYEPVVRPUElBX1RFU1RfQUExAAAAAAAcaAP1hgAFAQGAAgJvgQMCATIBAaCAAQeAASSCCAMB//wD/wADgAElggoEAf///wT/AAAAgAGJggYCAeAC/x+AAYqCBgIBwAL/P4ABi4IOBgGUAAD/+Ab/AAAAAAeAAYyCCgQB///gBP8AAB+AAY2CBAEAAf8BAsAAgIJMVUp2x5WNacXWRpvKchhjsd1yP92YgzWDn12PETgY7YCAglNasR1KApOsr5xX3kyeek2eDbKzzd7M5+SxcSn/I/5FgmGAV9vbLo+GyAgKndOwwOWAlGWUxtqzAJe7gLTLheTaqdR7puulu+wB6/L7hvUJPAnDFDfL/RYlTGpE0lZN3rzqQBTUN3fe1jlB7AvglB4Fwun16QJ4X/I8+7jcFRiJWBQM"
// PKIITS_CMDARG_ITS_EC_VKEY="MHcCAQEEIIQ80EJBAu3M2YIwV6bBIJXWAVyauRZ4/OJxCr5JUNzsoAoGCCqGSM49AwEHoUQDQgAEsddOL9IUVMNmbKJdDXwJdGCs3VIjMyITq6NnM3ov6LqNzP16kvgLJC5oOwVNEy9Hpdmng5jnlKNrbdeNxcXsTA=="
// PKIITS_CMDARG_ITS_EC_CERT="gAMAgGzCAjtRFQA+EYEtQkVOQ0gtSVRTUEtJLVVUT1BJQS0yMDE5MDgyMS01MUFDMzIxMjk2NTI2MjcxAAAAAAAddbU/hGaoAQGAAgJvgQMCAcAAgIQ53B6Qrg3qP0rzmzdoKZ3XvJQWAD6j1s3V2YUTh7/jnoeKB5WWbRvsfchhGXWUJfWFZM7Yd1KdmRKghNGhEDX+gICEsddOL9IUVMNmbKJdDXwJdGCs3VIjMyITq6NnM3ov6LqNzP16kvgLJC5oOwVNEy9Hpdmng5jnlKNrbdeNxcXsTIGAR2DMKQiGp5ft2f4cp5wy1j75pwFfw5FW8WPKnlKogG8f+vslg5al2DulM2sViHqcBs68YxCLsXdakAicAXJ5Qg=="
// PKIITS_CMDARG_ITS_AT_EKEY_ENABLE=true
// PKIITS_CMDARG_AT_PSIDSSP_SEQ="36:010000"
TEST(its_enrollment_at_request, add)
{
	ItsPkiCmdArguments cmd_args;
	defaultCmdArgs(cmd_args);

	ItsPkiInternalData idata;
	
	ASSERT_TRUE(ParseAtEnrollmentCmdArguments(cmd_args, idata));
	ItsPkiSession session(idata);

	OCTETSTRING request;
	ASSERT_TRUE(session.AtEnrollmentRequest_InnerAtRequest(idata, request));
	
	void *ea_prvkey = ECKey_ReadPrivateKeyB64(ea_eprvkey);
	void *aa_prvkey = ECKey_ReadPrivateKeyB64(aa_eprvkey);
	ASSERT_TRUE(session.AtEnrollmentRequest_Parse(request, ea_prvkey, aa_prvkey));

}
