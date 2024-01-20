import { Downloader } from "./Downloader";
import { ActionComplete, DownloadProgress } from "./Progress";

class Protocol {
  static DEFAULT_URL =
    "https://fe3.delivery.mp.microsoft.com/ClientWebService/client.asmx";
  static SECURED_URL =
    "https://fe3.delivery.mp.microsoft.com/ClientWebService/client.asmx/secured";

  static soap = "http://www.w3.org/2003/05/soap-envelope";
  static addressing = "http://www.w3.org/2005/08/addressing";
  static secext =
    "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd";
  static secutil =
    "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd";
  static wuws =
    "http://schemas.microsoft.com/msus/2014/10/WindowsUpdateAuthorization";
  static wuclient =
    "http://www.microsoft.com/SoftwareDistribution/Server/ClientWebService";

  _msaUserToken: string = "";

  setMSAUserToken(token: string) {
    this._msaUserToken = token;
  }

  buildWUTickets(): Element {
    const tickets = document.createElementNS(
      Protocol.wuws,
      "WindowsUpdateTicketsToken",
    );
    tickets.setAttribute("wsu:id", "ClientMSA");
    tickets.setAttribute("xmlns:wsu", Protocol.secutil);
    tickets.setAttribute("xmlns:wuws", Protocol.wuws);

    if (this._msaUserToken !== null) {
      const msaTicket = document.createElement("TicketType");
      msaTicket.setAttribute("Name", "MSA");
      msaTicket.setAttribute("Version", "1.0");
      msaTicket.setAttribute("Policy", "MBI_SSL");
      const userElement = document.createElement("User");
      userElement.textContent = this._msaUserToken;
      msaTicket.appendChild(userElement);
      tickets.appendChild(msaTicket);
    }

    const aadTicket = document.createElement("TicketType");
    aadTicket.setAttribute("Name", "AAD");
    aadTicket.setAttribute("Version", "1.0");
    aadTicket.setAttribute("Policy", "MBI_SSL");
    tickets.appendChild(aadTicket);

    return tickets;
  }

  buildHeader(url: string | null, methodName: string) {
    const now = new Date().toISOString();

    const header = document.createElementNS(Protocol.soap, "Header");

    const action = document.createElementNS(Protocol.addressing, "Action");
    action.textContent =
      "http://www.microsoft.com/SoftwareDistribution/Server/ClientWebService/" +
      methodName;
    action.setAttributeNS(Protocol.soap, "mustUnderstand", "1");
    header.appendChild(action);

    const messageID = document.createElementNS(
      Protocol.addressing,
      "MessageID",
    );
    messageID.textContent = "urn:uuid:5754a03d-d8d5-489f-b24d-efc31b3fd32d";
    header.appendChild(messageID);

    const to = document.createElementNS(Protocol.addressing, "To");
    to.textContent = url;
    to.setAttributeNS(Protocol.soap, "mustUnderstand", "1");
    header.appendChild(to);

    const security = document.createElementNS(Protocol.secext, "Security");
    security.setAttributeNS(Protocol.soap, "mustUnderstand", "1");
    security.setAttribute("xmlns:o", Protocol.secext);

    const timestamp = document.createElementNS(Protocol.secutil, "Timestamp");
    const created = document.createElementNS(Protocol.secutil, "Created");
    created.textContent = now;
    const expires = document.createElementNS(Protocol.secutil, "Expires");
    expires.textContent = new Date(new Date().getTime() + 5 * 60000)
      .toISOString();

    timestamp.appendChild(created);
    timestamp.appendChild(expires);

    security.appendChild(timestamp);
    security.appendChild(this.buildWUTickets()); // Assuming buildWUTickets is defined elsewhere

    header.appendChild(security);

    return header;
  }

  buildDownloadRequest(updateIdentity: string, revisionNumber: string) {
    const envelope = document.createElementNS(Protocol.soap, "Envelope");
    envelope.setAttribute("xmlns:a", Protocol.addressing);
    envelope.setAttribute("xmlns:s", Protocol.soap);

    const header = this.buildHeader(
      this.getDownloadUrl(),
      "GetExtendedUpdateInfo2",
    );
    envelope.appendChild(header);

    const body = document.createElementNS(Protocol.soap, "Body");

    const updateInfo2 = document.createElementNS(
      Protocol.wuclient,
      "GetExtendedUpdateInfo2",
    );

    const updateIds = document.createElementNS(Protocol.wuclient, "updateIDs");
    const updateIdentityElement = document.createElementNS(
      Protocol.wuclient,
      "UpdateIdentity",
    );
    const updateIDElement = document.createElementNS(
      Protocol.wuclient,
      "UpdateID",
    );
    updateIDElement.textContent = updateIdentity;
    updateIdentityElement.appendChild(updateIDElement);

    const revisionNumberElement = document.createElementNS(
      Protocol.wuclient,
      "RevisionNumber",
    );
    revisionNumberElement.textContent = revisionNumber;
    updateIdentityElement.appendChild(revisionNumberElement);
    updateIds.appendChild(updateIdentityElement);

    const infoTypes = document.createElementNS(Protocol.wuclient, "infoTypes");
    const xmlUpdateFragmentType = document.createElementNS(
      Protocol.wuclient,
      "XmlUpdateFragmentType",
    );
    xmlUpdateFragmentType.textContent = "FileUrl";
    infoTypes.appendChild(xmlUpdateFragmentType);

    const deviceAttributes = document.createElementNS(
      Protocol.wuclient,
      "deviceAttributes",
    );
    deviceAttributes.textContent =
      "E:BranchReadinessLevel=CBB&DchuNvidiaGrfxExists=1&ProcessorIdentifier=Intel64%20Family%206%20Model%2063%20Stepping%202&CurrentBranch=rs4_release&DataVer_RS5=1942&FlightRing=Retail&AttrDataVer=57&InstallLanguage=en-US&DchuAmdGrfxExists=1&OSUILocale=en-US&InstallationType=Client&FlightingBranchName=&Version_RS5=10&UpgEx_RS5=Green&GStatus_RS5=2&OSSkuId=48&App=WU&InstallDate=1529700913&ProcessorManufacturer=GenuineIntel&AppVer=10.0.17134.471&OSArchitecture=AMD64&UpdateManagementGroup=2&IsDeviceRetailDemo=0&HidOverGattReg=C%3A%5CWINDOWS%5CSystem32%5CDriverStore%5CFileRepository%5Chidbthle.inf_amd64_467f181075371c89%5CMicrosoft.Bluetooth.Profiles.HidOverGatt.dll&IsFlightingEnabled=0&DchuIntelGrfxExists=1&TelemetryLevel=1&DefaultUserRegion=244&DeferFeatureUpdatePeriodInDays=365&Bios=Unknown&WuClientVer=10.0.17134.471&PausedFeatureStatus=1&Steam=URL%3Asteam%20protocol&Free=8to16&OSVersion=10.0.17134.472&DeviceFamily=Windows.Desktop";

    updateInfo2.appendChild(updateIds);
    updateInfo2.appendChild(infoTypes);
    updateInfo2.appendChild(deviceAttributes);

    body.appendChild(updateInfo2);
    envelope.appendChild(body);

    return envelope;
  }

  getDownloadUrl() {
    return Protocol.SECURED_URL;
  }

  extractDownloadResponseUrls(doc: Document) {
    const namespaceManager = new XPathEvaluator().createNSResolver(
      doc.documentElement,
    );
    //@ts-ignore
    namespaceManager.lookupNamespaceURI = (prefix: string) => {
      switch (prefix) {
        case "s":
          return "http://www.w3.org/2003/05/soap-envelope";
        case "wu":
          return "http://www.microsoft.com/SoftwareDistribution/Server/ClientWebService";
        default:
          return null;
      }
    };

    const result = doc.evaluate(
      "/s:Envelope/s:Body/wu:GetExtendedUpdateInfo2Response/wu:GetExtendedUpdateInfo2Result",
      doc,
      namespaceManager,
      XPathResult.FIRST_ORDERED_NODE_TYPE,
      null,
    ).singleNodeValue as Element;

    if (!result) {
      return [];
    }

    const urls = doc.evaluate(
      "wu:FileLocations/wu:FileLocation/wu:Url",
      result,
      namespaceManager,
      XPathResult.ORDERED_NODE_ITERATOR_TYPE,
      null,
    );

    const urlArray: string[] = [];
    let urlNode = urls.iterateNext();
    while (urlNode) {
      urlArray.push(urlNode.textContent || "");
      urlNode = urls.iterateNext();
    }

    return urlArray;
  }
}

const protocol: Protocol = new Protocol();

async function postXmlAsync(url: RequestInfo | URL, data: Node) {
  const requestOptions = {
    method: "POST",
    headers: {
      "Content-Type": "application/soap+xml",
    },
    body: new XMLSerializer().serializeToString(data),
  };

  const response = await fetch(url, requestOptions);
  if (!response.ok) {
    console.log("Response is not OK!");
  }

  return new DOMParser().parseFromString(
    await response.text(),
    "application/xml",
  );
}

async function getDownloadUrl(updateIdentity: string, revisionNumber: string) {
  try {
    const result = await postXmlAsync(
      protocol.getDownloadUrl(),
      protocol.buildDownloadRequest(updateIdentity, revisionNumber),
    );

    console.log(
      `GetDownloadUrl() response for updateIdentity ${updateIdentity}, revision ${revisionNumber}:\n${result}`,
    );

    const downloadUrls = protocol.extractDownloadResponseUrls(result);

    for (const url of downloadUrls) {
      if (url.startsWith("http://tlu.dl.delivery.mp.microsoft.com/")) {
        return url;
      }
    }

    return null;
  } catch (error) {
    console.error("Error in GetDownloadUrl():", error);
    return null;
  }
}

export async function download(
  updateIdentity: string,
  revisionNumber: string,
  destination: string,
  onProgress: DownloadProgress = () => {},
  onComplete: ActionComplete = () => {},
) {
  const link: string | null = await getDownloadUrl(
    updateIdentity,
    revisionNumber,
  );
  if (link === null) {
    onComplete(false);
    throw new Error("BadUpdateIdentity!");
  }
  console.log("Resolved download link:", link);
  await Downloader.downloadFile(
    link,
    destination,
    onProgress,
    onComplete,
  );
}
